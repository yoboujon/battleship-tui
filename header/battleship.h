#ifndef HEADER_BATTLESHIP
#define HEADER_BATTLESHIP
#include <iostream>
#include <stdint.h>
#include <vcruntime.h>

#define LENGTH_BASE 10

class board
{
    private :
        char ** m_board;
        uint16_t m_width;
        uint16_t m_height;
    public :
        board();
        board(uint16_t width, uint16_t height);
        ~board();
        void printBoard();
};

#endif