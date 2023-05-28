#ifndef HEADER_BTUI_EXCEPTION
#define HEADER_BTUI_EXCEPTION

#include <exception>
#include <stdint.h>

class battleshipException : public std::exception {
private:
    const char* error;
    const uint32_t code;

public:
    battleshipException(uint32_t errorCode, const char* errorString);
    ~battleshipException();
    uint32_t getErrorCode(void);
    const char* getError(void);
};

#endif