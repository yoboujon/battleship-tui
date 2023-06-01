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
    if (commandParsed.command == "attack") {
        auto status = m_board.attack(position { static_cast<int8_t>(vars.byteArg[0]), static_cast<int8_t>(vars.byteArg[1]) });
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
}