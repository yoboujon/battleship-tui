#ifndef HEADER_COMMAND
#define HEADER_COMMAND

#include <map>
#include <stdint.h>
#include <string>
#include <vector>


namespace command {

enum ERR {
    FLOAT = 4,
    INT = 5,
    UINT = 6,
    NOTCHAR = 7,
    STRING = 8
};

typedef struct {
    std::vector<char> charArg;
    std::vector<uint8_t> byteArg;
    std::vector<int64_t> intArg;
    std::vector<uint64_t> uintArg;
    std::vector<double> doubleArg;
    std::vector<std::string> string;
} valuesArg;

typedef struct {
    std::string command;
    std::vector<std::string> args;
} completeCommand_t;

class commandGeneric {
private:
    void thrower(std::string argument, std::string errorString, bool testNegative, bool testFloat, bool testString, bool testChar);
protected:
    std::string m_cmd;
    std::map<std::string, std::string> m_commandMap;

    completeCommand_t m_commandParsed;
    valuesArg m_vars;

    /**
     * @brief With the given m_cmd, will return a vector of string of
     * all the arguments as well as the command itself in a form of a vector.
     *
     * @return completeCommand_t
     */
    completeCommand_t parser(void);

    /**
     * @brief will return the actual values from the command with the correct type.
     * If the conversion couldn't be done will return an error.
     *
     * @param cmd the vector of command and args
     * @return valuesArg in the correct order, the values of each type
     */
    valuesArg argParser(completeCommand_t completeCmd);

    void help(void);

public:
    commandGeneric();
    ~commandGeneric();

    void readCommand(std::string cmd);
};

class commandException : public std::exception {
private:
    std::string error;
    const uint32_t code;

public:
    commandException(uint32_t errorCode, std::string errorString);
    ~commandException();
    uint32_t getErrorCode(void);
    const char* getError(void);
};

}

#endif