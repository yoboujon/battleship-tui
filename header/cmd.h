#ifndef HEADER_COMMAND
#define HEADER_COMMAND

#include <string>
#include <vector>

class commandGeneric {
protected:
    std::string m_cmd;

    /**
     * @brief With the given m_cmd, will return a vector of string of
     * all the arguments as well as the command itself in a form of a vector.
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> parser(void);

public:
    commandGeneric();
    ~commandGeneric();
};

#endif