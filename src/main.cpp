#include <iostream>
#include <cpr/cpr.h>
#include "twitch.h"
#include <fstream>
#include <sstream>
#include <string>
#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <iostream>
#include <fstream>
#include <map>

std::ofstream linkFile ("../links.txt");

std::map<std::string, bool> linksFound;

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

void handleLink(std::string link) {
    std::map<std::string, bool>::iterator it = linksFound.find(link);

    if (it != linksFound.end()) {
        printMessage("Duplicate found, skipping: " + link);
        return;
    }

    printMessage("Saving link: " + link);
    linkFile << link << std::endl;
    linksFound.insert(std::pair<std::string, bool>(link, true));
}

void handleLine(std::string line)
{
    try
    {
        std::regex re("(https://[^ ]*)");
        std::smatch match;
        if (std::regex_search(line, match, re) && match.size() > 1)
        {
            handleLink(match.str(1));
        }
    }
    catch (std::regex_error &e)
    {
        printMessage("something went wrong");
        return;
    }
}

int main()
{
    std::ifstream file("../log.txt");
    std::string line;

    std::int64_t lineCount = 0;
    while (std::getline(file, line))
    {
        lineCount++;
        handleLine(line);
    }

    printMessage("Line count: " + std::to_string(lineCount));

    linkFile.close();

    return 0;
}
