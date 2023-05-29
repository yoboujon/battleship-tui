#include "cmd.h"
#include <iostream>
#include <string>

using namespace command;

commandGeneric::commandGeneric()
{
}

commandGeneric::~commandGeneric()
{
}

functionArgs commandGeneric::parser(void)
{
    functionArgs parsing;
    std::string copy_cmd(m_cmd), token;
    size_t pos(0);
    bool isArg(false);

    // While we still find the delimiter (space) we continue to gather the data
    while ((pos = copy_cmd.find(" ")) != std::string::npos) {
        // Token is assigned the cmd minus all the delimited data (by a space)
        token = copy_cmd.substr(0, pos);
        // We then push back the parser into the command, args otherwise
        if (isArg)
            parsing.args.push_back(token);
        else {
            parsing.command = token;
            isArg = true;
        }
        // We erase the established data plus the delimiter (space)
        copy_cmd.erase(0, pos + 1);
    }
    // We get the last argument
    parsing.args.push_back(copy_cmd.substr(pos + 1, copy_cmd.size()));
    return parsing;
}