#include "exception.h"

battleshipException::battleshipException(uint32_t errorCode, const char* errorString)
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
    return error;
}