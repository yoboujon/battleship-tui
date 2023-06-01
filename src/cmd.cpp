#include "cmd.h"
#include <iostream>
#include <stdint.h>
#include <string>

using namespace command;

/*------------------------------------------------------*/
/*                    Command Generic                   */
/*------------------------------------------------------*/

commandGeneric::commandGeneric()
{
}

commandGeneric::~commandGeneric()
{
}

completeCommand_t commandGeneric::parser(void)
{
    completeCommand_t parsing;
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

/**
 * * For now only does the c,b,u and i types.*
 * TODO : Implement the string case 's'
 * ! If the user enters a string it doesn't detect it for now
 * ! Maybe optimizing the code could be a good idea because there are like 10 lines of code that are the same...
 */
valuesArg commandGeneric::argParser(completeCommand_t completeCmd)
{
    valuesArg returnValuesArg;
    int i(0);
    /*Tests if the command actually exists.*/
    if (m_commandMap.find(completeCmd.command) == m_commandMap.end())
        throw commandException(1, "'" + completeCmd.command + "': command not found, type 'help' for a list of installed component.");
    /*Tests if the number of argument is complient with the command typed*/
    if (completeCmd.args.size() != m_commandMap[completeCmd.command].size())
        throw commandException(2, "'" + completeCmd.command + "' asks for " + std::to_string(m_commandMap[completeCmd.command].size()) + " arguments, " + std::to_string(completeCmd.args.size()) + " provided.");
    for (auto expectedType : m_commandMap[completeCmd.command]) {
        switch (expectedType) {
        case 'c':
            if (completeCmd.args[i].size() > 1)
                throw commandException(NOTCHAR, "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be a char.");
            returnValuesArg.charArg.push_back(completeCmd.args[i][0]);
            break;
        case 'b':
            if (completeCmd.args[i].find('.') != std::string::npos)
                throw commandException(FLOAT, "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be an unsigned byte.");
            if (std::stoi(completeCmd.args[i]) < 0)
                throw commandException(INT, "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be an unsigned byte.");
            returnValuesArg.byteArg.push_back(static_cast<uint8_t>(std::stoi(completeCmd.args[i])));
            break;
        case 'u':
            if (completeCmd.args[i].find('.') != std::string::npos)
                throw commandException(FLOAT, "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be an unsigned number.");
            if (std::stoll(completeCmd.args[i]) < 0)
                throw commandException(INT, "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be an unsigned number.");
            returnValuesArg.uintArg.push_back(std::stoll(completeCmd.args[i]));
            break;
        case 'i':
            if (completeCmd.args[i].find('.') != std::string::npos)
                throw commandException(FLOAT, "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be a whole number.");
            returnValuesArg.intArg.push_back(std::stoll(completeCmd.args[i]));
            break;
        default:
            throw commandException(3, "'" + completeCmd.command + "': Invalid command mapping.");
            break;
        }
        i++;
    }
    return returnValuesArg;
}

/*------------------------------------------------------*/
/*                    Command Exception                 */
/*------------------------------------------------------*/

commandException::commandException(uint32_t errorCode, std::string errorString)
    : error(errorString)
    , code(errorCode)
{
}

commandException::~commandException()
{
}

uint32_t commandException::getErrorCode(void)
{
    return code;
}

const char* commandException::getError(void)
{
    return error.c_str();
}