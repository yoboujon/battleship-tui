#include "battleship.h"
#include "exception.h"
#include <stdint.h>
#include <vector>

using namespace battleshiptui;

int main(void)
{
    board coolBoard(loglevel::NORMAL);
    std::vector<uint8_t> boatSetup = { 2, 2, 2, 3, 3, 4, 5 };
    coolBoard.printBoard();
    try {
        coolBoard.createBoats(boatSetup);
    } catch (battleshipException& e) {
        std::cout << "Battleship-TUI Error " << e.getErrorCode() << ": " << e.getError() << std::endl;
        return 0;
    }
    std::cout << std::endl;
    coolBoard.printBoard();
    return 0;
}