#include "cmd_battleship.h"
#include "battleship.h"
#include <functional>
#include <stdint.h>

using namespace battleshiptui;

commandBattleship::commandBattleship(board& actualBoard)
    : m_board(actualBoard)
{
    m_commandMap.insert({ "attack", "bb" });
    m_commandMap.insert({ "terminate", ""});
    m_commandMap.insert({ "testfloat", "f" });
    m_commandMap.insert({ "teststring", "s" });
}

commandBattleship::~commandBattleship()
{
}

void commandBattleship::readCommand(std::string cmd)
{
    commandGeneric::readCommand(cmd);
    if (m_commandParsed.command == "attack") {
        auto status = m_board.attack(position { static_cast<int8_t>(m_vars.byteArg[0]), static_cast<int8_t>(m_vars.byteArg[1]) });
        switch (status) {
        case boatStatus::HIT:
            std::cout << "Boat hit !" << std::endl;
            break;
        case boatStatus::SPLASHBOAT:
            std::cout << "Boat already hit !" << std::endl;
            break;
        case boatStatus::SPLASHWATER:
            std::cout << "SLASH !" << std::endl;
            break;
        case boatStatus::SUNK:
            std::cout << "Boat has sunk !" << std::endl;
            break;
        default:
            std::cout << "attack : Undefined Behavior" << std::endl;
            break;
        }
    }
    if(m_commandParsed.command == "terminate")
    {
        m_board.finishGame();
    }
}