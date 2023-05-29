#ifndef HEADER_BTUI_COMMAND
#define HEADER_BTUI_COMMAND

#include "battleship.h"
#include "cmd.h"
#include <string>
#include <vector>
#include <map>

namespace battleshiptui {

class commandBattleship : public command::commandGeneric {
private:
    board& m_board;
public:
    commandBattleship(board& actualBoard);
    ~commandBattleship();
    void readCommand(std::string cmd);
};

};

#endif