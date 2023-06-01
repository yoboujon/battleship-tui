#include "battleship.h"
#include "cmd.h"
#include "cmd_battleship.h"
#include "exception.h"
#include <stdint.h>
#include <string>
#include <vector>

using namespace battleshiptui;

int main(void)
{
    board userBoard(loglevel::DEBUG);
    commandBattleship userCommand(userBoard);
    std::string userInput;
    std::vector<uint8_t> boatSetup = { 2, 2, 2, 3, 3, 4, 5 };

    // Init
    try {
        userBoard.createBoats(boatSetup);
    } catch (battleshipException& e) {
        std::cout << "Battleship-TUI Error " << e.getErrorCode() << ": " << e.getError() << std::endl;
        return 0;
    }

    // Step
    while (!userBoard.isGameFinished()) {
        std::cout << "Enter a command." << std::endl;
        std::getline(std::cin, userInput);
        try {
            userCommand.readCommand(userInput);
        } catch (command::commandException& e) {
            std::cout << e.getError() << std::endl;
        } catch (battleshipException& e) {
            std::cout << "Battleship-TUI Error " << e.getErrorCode() << ": " << e.getError() << std::endl;
        }
    }

    // userBoard.printBoard();
    return 0;
}