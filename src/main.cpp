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

std::ofstream linkFile ("../links.txt");

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
    linkFile << link << std::endl;
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
        return;
    }
}

int main()
{
    std::ifstream file("../log.txt");
    std::string line;

    std::int64_t lineCount = 0;
    std::int64_t wordCount = 0;
    std::int64_t privmsgCount = 0;
    std::int64_t clearchatCount = 0;
    std::int64_t usernoticeCount = 0;
    while (std::getline(file, line))
    {
        handleLine(line);
        lineCount++;
        auto words = split(line, ' ');
        wordCount += words.size();

        if (words[2] == TwitchMessageTypes::PRIVMSG)
        {
            privmsgCount++;
        }
        else if (words[2] == TwitchMessageTypes::CLEARCHAT)
        {
            clearchatCount++;
        }
        else if (words[2] == TwitchMessageTypes::USERNOTICE)
        {
            usernoticeCount++;
        }
        else
        {
            std::cout << words[2] + "\n";
        }
    }

    printMessage("Line count: " + std::to_string(lineCount));
    printMessage("Word count: " + std::to_string(wordCount));
    printMessage("Privmsg count: " + std::to_string(privmsgCount));
    printMessage("Clearchat count: " + std::to_string(clearchatCount));
    printMessage("Usernotice count: " + std::to_string(usernoticeCount));

    linkFile.close();

    return 0;
}
