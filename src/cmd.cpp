#include "cmd.h"
#include <iostream>
#include <string>

commandGeneric::commandGeneric()
{
}

commandGeneric::~commandGeneric()
{
}

std::vector<std::string> commandGeneric::parser(void)
{
    std::vector<std::string> parsing;
    std::string copy_cmd(m_cmd), token;
    size_t pos(0);

    // While we still find the delimiter (space) we continue to gather the data
    while ((pos = copy_cmd.find(" ")) != std::string::npos) {
        // Token is assigned the cmd minus all the delimited data (by a space)
        token = copy_cmd.substr(0, pos);
        // We then push back the parser
        parsing.push_back(token);
        // We erase the established data plus the delimiter (space)
        copy_cmd.erase(0, pos + 1);
    }
    // We get the last argument
    parsing.push_back(copy_cmd.substr(pos + 1, copy_cmd.size()));
    return parsing;
}