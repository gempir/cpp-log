#include <iostream>
#include <cpr/cpr.h>
#include "twitch.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <filesystem>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <cpr/cpr.h>
#include <functional>

std::hash<std::string> hasher;

namespace fs = std::filesystem;

std::ofstream linkFile ("../links.txt");

std::map<std::string, bool> linksFound;

std::regex re("(https://[^ ]*(\\.jpg|\\.png|\\.gif)|https://gyazo.com/[^ ]*)");

std::string lastN(std::string input, int n)
{
     return input.substr(input.size() - n);
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }

    return elems;
}

void printMessage(std::string msg)
{
    std::cout << msg << std::endl;
}

void downloadLink(std::string link) {
    auto r = cpr::Get(cpr::Url{link}, cpr::VerifySsl(false));
    
    std::string filename = std::to_string(std::hash<std::string>{}(link));
    filename += lastN(link, 4);

    std::ofstream image ("../images/" + filename);
    image << r.text;
    image.close();
}

void handleLink(std::string link) {
    std::map<std::string, bool>::iterator it = linksFound.find(link);

    if (it != linksFound.end()) {
        return;
    }

    linkFile << link << std::endl;
    downloadLink(link);
    linksFound.insert(std::pair<std::string, bool>(link, true));
}

void handleLine(std::string line)
{
    try
    {
        std::smatch match;
        if (std::regex_search(line, match, re) && match.size() > 1)
        {
            auto link = match.str(1);
            if (link.find("gyazo.com") != std::string::npos) {
                link += ".png";
            }

            handleLink(link);
        }
    }
    catch (std::regex_error &e)
    {
        printMessage("something went wrong");
        return;
    }
}

void scanLog(std::string filePath) {
    printMessage("Opening: " + filePath);
    std::ifstream file(filePath, std::ios_base::in | std::ios_base::binary);
    try {
        boost::iostreams::filtering_istream in;
        in.push(boost::iostreams::gzip_decompressor());
        in.push(file);
        
        std::string str;
        str.reserve(5000);

        while(std::getline(in, str))
        {
            handleLine(str);
        }
    }
    catch(const boost::iostreams::gzip_error& e) {
         std::cout << e.what() << '\n';
    }
}

int main()
{
    std::string path = "../logs";

    for(auto itEntry = fs::recursive_directory_iterator(path); itEntry != fs::recursive_directory_iterator(); ++itEntry )
    {
        scanLog(itEntry->path().string());
    }

    linkFile.close();

    return 0;
}

