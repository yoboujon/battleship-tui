#include "cmd_battleship.h"
#include "battleship.h"
#include <functional>
#include <stdint.h>

using namespace battleshiptui;

commandBattleship::commandBattleship(board& actualBoard)
    : m_board(actualBoard)
{
    m_commandMap.insert({ "attack", "bb" });
    m_commandMap.insert({ "terminate", "" });
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
        attack();
    }
    if (m_commandParsed.command == "terminate") {
        terminate();
    }
    if(m_commandParsed.command == "testfloat")
    {
        std::cout << "Gathered float: " << m_vars.doubleArg[0] << std::endl;
    }
     if(m_commandParsed.command == "teststring")
    {
        std::cout << "Gathered string: " << m_vars.string[0] << std::endl;
    }
}

void commandBattleship::attack(void)
{
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

void commandBattleship::terminate(void)
{
    m_board.finishGame();
    std::cout << "\nHere was the board :" << std::endl;
    m_board.printBoard(true);
    std::cout << "You sunk" << (int)(m_board.getSunkcount()) << " boats." << std::endl;
}