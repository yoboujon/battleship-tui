#ifndef HEADER_BTUI_COMMAND
#define HEADER_BTUI_COMMAND

#include "battleship.h"
#include "cmd.h"
#include <string>
#include <vector>

namespace battleshiptui {

class commandBattleship : public commandGeneric {
private:
public:
    commandBattleship();
    ~commandBattleship();
    void readCommand(std::string cmd);
};

};

#endif