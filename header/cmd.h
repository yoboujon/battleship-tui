#ifndef HEADER_COMMAND
#define HEADER_COMMAND

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

namespace command {

typedef struct{
    std::vector<int64_t> intArg;
    std::vector<uint64_t> uintArg;
    std::vector<double> doubleArg;
    std::vector<std::string> string;
} commandArgs;

typedef struct{
    std::string command;
    std::vector<std::string> args;
} functionArgs;

class commandGeneric {
protected:
    std::string m_cmd;
    std::map<std::string, std::string> m_commandMap;

    /**
     * @brief With the given m_cmd, will return a vector of string of
     * all the arguments as well as the command itself in a form of a vector.
     * 
     * @return std::vector<std::string> 
     */
    functionArgs parser(void);

    commandArgs  argParser(std::string, std::vector<std::string> args);

public:
    commandGeneric();
    ~commandGeneric();
};

}

#endif