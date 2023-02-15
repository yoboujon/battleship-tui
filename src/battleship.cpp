#include "../header/battleship.h"
#include <vcruntime.h>

/**     ---     BOARD       ---      **/

board::board(): board(LENGTH_BASE, LENGTH_BASE){}

board::board(uint16_t width, uint16_t height): m_width(width), m_height(height)
{
    m_board = new char*[height];
    for(int i=0;i<height;i++)
    {
        /**Thanks to 1iMAngie**/
        m_board[i] = new char[width];
        memset(m_board[i],'a',width);
    }
}

board::~board()
{
    /**We remove each pointer in the pointer array to avoid memory leaks when clearing the board.
    Idea by 1iMAngie**/
    for(size_t i=0;i<m_height;i++)
    {
        delete[] m_board[i];
    }
    /**We still remove the base double pointer at the end**/
    delete m_board;
}

void board::printBoard()
{
    for(int i=0;i<m_width;i++)
    {
        for(int j=0;j<m_height;j++)
        {
            std::cout << "[" << m_board[i][j] << "] ";
        }
        std::cout << "\n";
    }   
}

void board::createBoats(std::vector<uint8_t> boatsNumber)
{
    std::srand((unsigned int)std::time(0));
    for(auto boat:boatsNumber)
    {
        battleship tempBattleShip(boat,(direction)(std::rand()%3),(uint8_t)(std::rand()%10),(uint8_t)(std::rand()%10));
        tempBattleShip.printBoat();
        m_battleships.push_back(tempBattleShip);

    }
}

/**     ---     BOATS       ---      **/

battleship::battleship(uint8_t size,direction orientation, uint8_t x, uint8_t y):m_size(size),m_orientation(orientation),m_x(x),m_y(y){}

void battleship::printBoat()
{
    std::cout << "Size :" << (int)m_size << "\tOrientation: " << (int)m_orientation << "\t x=" << (int)m_x << "\t y=" << (int)m_y << std::endl;
}