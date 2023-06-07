#include "cmd.h"
#include <cctype>
#include <iostream>
#include <locale>
#include <stdint.h>
#include <string>

using namespace command;

/*------------------------------------------------------*/
/*                    Command Generic                   */
/*------------------------------------------------------*/

commandGeneric::commandGeneric()
{
    m_commandMap = { { "help", "" } };
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
    if (isArg)
        parsing.args.push_back(copy_cmd.substr(pos + 1, copy_cmd.size()));
    else
        parsing.command = copy_cmd;
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
        //char
        case 'c':
            thrower(completeCmd.args[i], "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be a char.", false, false, false, true);
            returnValuesArg.charArg.push_back(completeCmd.args[i][0]);
            break;
        //byte (uchar)
        case 'b':
            thrower(completeCmd.args[i], "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be an unsigned byte.", true, true, true, false);
            returnValuesArg.byteArg.push_back(static_cast<uint8_t>(std::stoi(completeCmd.args[i])));
            break;
        //uint
        case 'u':
            thrower(completeCmd.args[i], "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be an unsigned number.", true, true, true, false);
            returnValuesArg.uintArg.push_back(std::stoll(completeCmd.args[i]));
            break;
        //int
        case 'i':
            thrower(completeCmd.args[i], "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be a whole number.", false, true, true, false);
            returnValuesArg.intArg.push_back(std::stoll(completeCmd.args[i]));
            break;
        //float/double
        case 'f':
            thrower(completeCmd.args[i], "'" + completeCmd.command + "': argument " + std::to_string(i + 1) + " must be a float.", false, false, true, false);
            returnValuesArg.doubleArg.push_back(std::stod(completeCmd.args[i]));
            break;
        //string
        case 's':
            returnValuesArg.string.push_back(completeCmd.args[i]);
            break;
        default:
            throw commandException(3, "'" + completeCmd.command + "': Invalid command mapping.");
            break;
        }
        i++;
    }
    return returnValuesArg;
}

void commandGeneric::readCommand(std::string cmd)
{
    m_cmd = cmd;
    m_commandParsed = parser();
    m_vars = argParser(m_commandParsed);
    if (m_commandParsed.command == "help")
        help();
}

void commandGeneric::help(void)
{
    std::cout << "help is in WIP for now." << std::endl;
}

void commandGeneric::thrower(std::string argument, std::string errorString, bool testNegative, bool testFloat, bool testString, bool testChar)
{
    /*testChar checks if the size of the string is =1*/
    if ((argument.size() > 1) && testChar)
        throw commandException(NOTCHAR, errorString);
    /*testString checks if all the characters are either numbers or a '.'(for float nums)*/
    if (testString) {
        std::locale loc;
        for (unsigned long i(0); i < argument.size(); i++) {
            if (!(((argument[i] >= 0x30) && (argument[i] < 0x39)) || (argument[i] == '.') || (argument[i] == '-')))
                throw commandException(STRING, errorString);
        }
    }
    /* testFloat checks if there is a dot, aka float number*/
    if ((argument.find('.') != std::string::npos) && testFloat)
        throw commandException(FLOAT, errorString);
    /* testNegative checks if the converted long long value is negative*/
    if ((std::stoll(argument) < 0) && testNegative)
        throw commandException(INT, errorString);
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