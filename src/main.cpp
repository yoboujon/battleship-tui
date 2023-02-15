#include "../header/battleship.h"
#include <stdint.h>
#include <vector>

int main(void)
{
    board coolBoard;
    std::vector<uint8_t> boatSetup = {2,2,2,3,3,4,5};
    coolBoard.printBoard();
    coolBoard.createBoats(boatSetup);
    return 0;
}