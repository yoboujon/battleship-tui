#include "cmd_battleship.h"
#include <functional>

using namespace battleshiptui;

commandBattleship::commandBattleship(board& actualBoard)
    : m_board(actualBoard)
{
    m_commandMap = { { "attack", "uu" },
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

    std::cout << "Command entered: " << commandParsed.command << std::endl;
    for (auto& arg : commandParsed.args) {
        std::cout << "'" << arg << "'\t";
    }
    std::cout << std::endl;
}