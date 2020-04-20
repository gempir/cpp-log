#include <iostream>
#include <cpr/cpr.h>
#include "gempir.h"
#include <fstream>
#include <sstream>
#include <string>
#include <string>
#include <sstream>
#include <vector>

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



int main()
{
    // std::cout << GEMPIR << std::endl;

    std::ifstream file("../log.txt");
    std::string line;

    std::int64_t lineCount = 0;
    std::int64_t wordCount = 0;
    std::int64_t privmsgCount = 0;
    std::int64_t clearchatCount = 0;
    std::int64_t usernoticeCount = 0;
    while (std::getline(file, line))
    {
        lineCount++;
        auto words = split(line, ' ');
        wordCount += words.size();

        if  (words[2] == "PRIVMSG") {
            privmsgCount++;
        } else if (words[2] == "CLEARCHAT")
        {
            clearchatCount++;   
        } else if (words[2] == "USERNOTICE") {
            usernoticeCount++;
        } else {
            std::cout << words[2] + "\n";
        }
    }

    std::cout << std::printf("Line count: %d", lineCount);
    std::cout << "\n";
    std::cout << std::printf("Word count: %d", wordCount);
    std::cout << "\n";
    std::cout << std::printf("Privmsg count: %d", privmsgCount);
    std::cout << "\n";
    std::cout << std::printf("Clearchat count: %d", clearchatCount);
    std::cout << "\n";
    std::cout << std::printf("Usernotice count: %d", usernoticeCount);
    std::cout << "\n";

    return 0;
}


// for (auto it = words.cbegin(); it != words.cend(); it++)
//         {
//             if  (*it == "PRIVMSG") {
//                 privmsgCount++;
//             } else
//             {
//                 std::cout << *it + "\n";
//             }
            
//         }