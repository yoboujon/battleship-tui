#include "../header/battleship.h"

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