#include "cmd_battleship.h"
#include "battleship.h"
#include <functional>
#include <stdint.h>

using namespace battleshiptui;

commandBattleship::commandBattleship(board& actualBoard)
    : m_board(actualBoard)
{
    m_commandMap = { { "attack", "bb" },
        { "testfloat", "f" },
        { "teststring", "s" } };
}

commandBattleship::~commandBattleship()
{
}

void commandBattleship::readCommand(std::string cmd)
{
    m_cmd = cmd;
    auto commandParsed = parser();
    auto vars = argParser(commandParsed);
    if (commandParsed.command == "attack")
        m_board.attack(position { static_cast<int8_t>(vars.byteArg[0]), static_cast<int8_t>(vars.byteArg[1]) });
}