#include "exception.h"
#include <string>

using namespace battleshiptui;

battleshipException::battleshipException(uint32_t errorCode, std::string errorString)
    : error(errorString)
    , code(errorCode)
{
}

battleshipException::~battleshipException()
{
}

uint32_t battleshipException::getErrorCode(void)
{
    return code;
}

const char* battleshipException::getError(void)
{
    return error.c_str();
}