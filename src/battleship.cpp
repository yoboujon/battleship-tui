#include "../header/battleship.h"
#include <stdint.h>
#include <vcruntime.h>

/**     ---     BOARD       ---      **/

board::board(): board(LENGTH_BASE, LENGTH_BASE){}

board::board(uint16_t width, uint16_t height): m_width(width), m_height(height)
{
    /**We allocate the given pointer to the height it has been given**/
    m_board = new char*[height];
    for(int i=0;i<height;i++)
    {
        /**For every height, we allocate the width to the pointer pointed
        * Thanks to 1iMAngie during my livestream <3**/
        m_board[i] = new char[width];
        memset(m_board[i],BASE_CHAR,width);
    }
}

board::~board()
{
    /**We remove each pointer in the pointer array to avoid memory leaks when clearing the board.
     * Idea by 1iMAngie during my livestream**/
    for(size_t i=0;i<m_height;i++)
    {
        delete[] m_board[i];
    }
    /**We still remove the base double pointer at the end**/
    delete m_board;
}

void board::printBoard()
{
    /**From the given width and height will print out the board.**/
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
    /**the random device that will seed the generator then make a mersenne twister engine**/
    std::random_device seeder;
    std::mt19937 engine(seeder());
    /**for every size of boat**/
    for(auto boatSize:boatsNumber)
    {
        battleship tempBattleShip(boatSize,(direction)(std::rand()%3));
        /**Algorithm that will dodge negative values or values that exceed the width/height. Will be explained soon in the readme.**/
        std::uniform_int_distribution<int> tempX(
            0-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),false,true).x)*(boatSize-1),
            m_width-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),true).x)*(boatSize-1));
        std::cout << "[X] Direction : " << direction2string(tempBattleShip.getOrientation()) << "\t Min : " << 0-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),false,true).x)*(boatSize-1)
        << "\t Max : " << m_width-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),true).x)*(boatSize-1) << std::endl ;
        std::uniform_int_distribution<int> tempY(
            0-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),false,true).y)*(boatSize-1),
            m_height-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),true).y)*(boatSize-1));
        std::cout << "[Y] Direction : " << direction2string(tempBattleShip.getOrientation()) << "\t Min : " << 0-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),false,true).y)*(boatSize-1)
        << "\t Max : " << m_width-(tempBattleShip.positionOperatorFromOrientation(tempBattleShip.getOrientation(),true).y)*(boatSize-1) << std::endl ;
        tempBattleShip.setBasePosition((int8_t)tempX(engine),(int8_t)tempY(engine));
        /*      Debug Purpose only*/
        tempBattleShip.printBoat();
        printVector(tempBattleShip.placeBoat());

        /**We update the vector of boats inside the object**/
        m_battleships.push_back(tempBattleShip);
    }
}

/**     ---     BOATS       ---      **/

battleship::battleship(uint8_t size,direction orientation):m_size(size),m_orientation(orientation){}

void battleship::setBasePosition(int8_t x, int8_t y)
{
    m_position = {x,y};
}

void battleship::printBoat()
{
    std::cout << "Size :" << (int)m_size << "\tOrientation: " << direction2string(m_orientation) << "\t x=" << (int)m_position.x << "\t y=" << (int)m_position.y << std::endl;
}

position battleship::positionOperatorFromOrientation(direction orientation, bool noNegative, bool noPositive)
{
    position returnPos{0,0};
    int8_t negValue = noNegative ? 0:-1;
    int8_t posValue = noPositive ? 0:1;
    /**Like a compass, for any given direction, we could increment or decrement a given axis. We return these axis.**/
    switch(orientation)
    {
        case NORTH:
            returnPos.y = negValue;
            break;
        case SOUTH:
            returnPos.y = posValue;
            break;
        case EAST:
            returnPos.x = posValue;
            break;
        case WEST:
            returnPos.x = negValue;
            break;
    }
    return returnPos;
}

std::vector<position> battleship::placeBoat()
{
    std::vector<position> returnVector;
    position operatorPosition;
    /**We update the position vector for each given size, with the good orientation**/
    for(int8_t i=0;i<m_size;i++)
    {
        /**We get the operator (+ or -) for the given orientation**/
        operatorPosition = positionOperatorFromOrientation(m_orientation);
        /**The position is determined with the given orientation, at any given position the x or y axis should increment or decrement by i factor.**/
        returnVector.push_back({static_cast<int8_t>(m_position.x+((operatorPosition.x)*i)),static_cast<int8_t>(m_position.y+((operatorPosition.y)*i))});
    }
    return returnVector;
}

direction battleship::getOrientation()
{
    return m_orientation;
}

/**     ---     BASE FUNCTIONS       ---      **/


void printVector(std::vector<position> vector)
{
    for(auto value:vector)
    {
        std::cout << "x =" << (int)value.x << ", y =" << (int)value.y << "\t";
    }
    std::cout << std::endl;
}

const char * direction2string(direction orientation)
{
    switch(orientation)
    {
        case NORTH:
            return "NORTH";
        case SOUTH:
            return "SOUTH";
        case EAST:
            return "EAST";
        case WEST:
            return "WEST";
        default:
            break;
    }
    return "UNKNWON";
}