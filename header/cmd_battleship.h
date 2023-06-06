#ifndef HEADER_BTUI_COMMAND
#define HEADER_BTUI_COMMAND

#include "battleship.h"
#include "cmd.h"
#include <map>
#include <string>
#include <vector>


namespace battleshiptui {

class commandBattleship : public command::commandGeneric {
private:
    board& m_board;
    void attack(void);
    void terminate(void);

public:
    commandBattleship(board& actualBoard);
    ~commandBattleship();
    void readCommand(std::string cmd);
};

};

#endif