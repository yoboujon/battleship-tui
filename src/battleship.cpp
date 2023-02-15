#include "../header/battleship.h"
#include <stdint.h>
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
        printVector(tempBattleShip.placeBoat());
        m_battleships.push_back(tempBattleShip);
    }
}

/**     ---     BOATS       ---      **/

battleship::battleship(uint8_t size,direction orientation, int8_t x, int8_t y):m_size(size),m_orientation(orientation),m_position({x,y}){}

void battleship::printBoat()
{
    std::cout << "Size :" << (int)m_size << "\tOrientation: " << (int)m_orientation << "\t x=" << (int)m_position.x << "\t y=" << (int)m_position.y << std::endl;
}

std::vector<position> battleship::placeBoat()
{
    std::vector<position> returnVector;
    int8_t operatorX =0, operatorY=0;
    switch(m_orientation)
    {
        case NORTH:
            operatorY++;
            break;
        case SOUTH:
            operatorY--;
            break;
        case EAST:
            operatorX++;
            break;
        case WEST:
            operatorX--;
            break;
    }
    for(int8_t i=0;i<m_size;i++)
    {
        returnVector.push_back({static_cast<int8_t>(m_position.x+(operatorX*i)),static_cast<int8_t>(m_position.y+(operatorY*i))});
    }
    return returnVector;
}

void printVector(std::vector<position> vector)
{
    for(auto value:vector)
    {
        std::cout << "x =" << (int)value.x << ", y =" << (int)value.y << "\t";
    }
    std::cout << std::endl;
}