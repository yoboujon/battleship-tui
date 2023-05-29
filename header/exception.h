#ifndef HEADER_BTUI_EXCEPTION
#define HEADER_BTUI_EXCEPTION

#include <exception>
#include <stdint.h>
#include <string>

namespace battleshiptui {

class battleshipException : public std::exception {
private:
    std::string error;
    const uint32_t code;

public:
    battleshipException(uint32_t errorCode, std::string errorString);
    ~battleshipException();
    uint32_t getErrorCode(void);
    const char* getError(void);
};

}

#endif