#include "../header/battleship.h"
#include <stdint.h>
#include <vector>

using namespace battleshiptui;

int main(void)
{
    board coolBoard(loglevel::NORMAL);
    std::vector<uint8_t> boatSetup = { 2, 2, 2, 3, 3, 4, 5 };
    coolBoard.printBoard();
    coolBoard.createBoats(boatSetup);
    std::cout << std::endl;
    coolBoard.printBoard();
    return 0;
}