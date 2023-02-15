#ifndef HEADER_BATTLESHIP
#define HEADER_BATTLESHIP
#include <iostream>
#include <stdint.h>
#include <vcruntime.h>
#include <vector>
#include <cstdlib>
#include <ctime>
	

#define LENGTH_BASE 10

enum direction{ 
    NORTH,
    SOUTH,
    EAST,
    WEST
};

typedef struct{
    int8_t x;
    int8_t y;
} position;

class battleship
{
    private:
        uint8_t m_size;
        direction m_orientation;
        position m_position;
    public:
        battleship(uint8_t size,direction orientation, int8_t x, int8_t y);
        void printBoat();
        std::vector<position> placeBoat();
};

class board
{
    private :
        char ** m_board;
        uint16_t m_width;
        uint16_t m_height;
        std::vector<battleship> m_battleships;
    public :
        board();
        board(uint16_t width, uint16_t height);
        ~board();
        void printBoard();
        void createBoats(std::vector<uint8_t> boatsNumber);
};

void printVector(std::vector<position> vector);

#endif