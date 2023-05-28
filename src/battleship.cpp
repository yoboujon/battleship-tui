#include "../header/battleship.h"
#include <stdint.h>

/**     ---     BOARD       ---      **/

board::board()
    : board(LENGTH_BASE, LENGTH_BASE)
{
}

board::board(uint16_t width, uint16_t height)
    : m_width(width)
    , m_height(height)
{
    /**We allocate the given pointer to the height it has been given**/
    m_board = new char*[height];
    for (int i = 0; i < height; i++) {
        /**For every height, we allocate the width to the pointer pointed
         * Thanks to 1iMAngie during my livestream <3**/
        m_board[i] = new char[width];
        memset(m_board[i], BASE_CHAR, width);
    }
}

board::~board()
{
    /**We remove each pointer in the pointer array to avoid memory leaks when clearing the board.
     * Idea by 1iMAngie during my livestream**/
    for (size_t i = 0; i < m_height; i++) {
        delete[] m_board[i];
    }
    /**We still remove the base double pointer at the end**/
    delete m_board;
}

void board::printBoard()
{
    /**From the given width and height will print out the board.**/
    for (int i = 0; i < m_width; i++) {
        for (int j = 0; j < m_height; j++) {
            std::cout << "[" << m_board[i][j] << "] ";
        }
        std::cout << "\n";
    }
}

void board::createBoats(std::vector<uint8_t> boatsNumber)
{
    /**the random device that will seed the generator then make a mersenne twister engine**/
    std::random_device seeder;
    std::mt19937 engine(50);
    bool isColliding(false);
    /**for every size of boat**/
    for (auto boatSize : boatsNumber) {
        battleship tempBattleShip(boatSize, (direction)(std::rand() % 3));
        do {
            /**Algorithm that will dodge negative values or values that exceed the width/height.
             * * pSize = possible Size, pOFO = positionOperatorFromOrientation
             * the tempX explained with uniform_int_distribution(min,max) :
             * The minimum value is 0-pSize, With pSize = size if WEST (-pSize because pOFO only returns negative values here) (so either 0, or size)
             * The maximum value is maxWidth-pSize, with pSize = size if EAST (so either maxWidth, or maxWidth-size)
             * the tempY explained with uniform_int_distribution(min,max) :
             * The minimum value is 0-pSize, With pSize = size if NORTH (-pSize because pOFO only returns negative values here) (so either 0, or size)
             * The maximum value is maxWidth-pSize, with pSize = size if SOUTH (so either maxWidth, or maxWidth-size)**/
            std::uniform_int_distribution<int> tempX(
                0 + ((tempBattleShip.getOrientation() == direction::WEST) * (boatSize - 1)),
                m_width - ((tempBattleShip.getOrientation() == direction::EAST) * (boatSize - 1)));
            std::uniform_int_distribution<int> tempY(
                0 + ((tempBattleShip.getOrientation() == direction::NORTH) * (boatSize - 1)),
                m_height - ((tempBattleShip.getOrientation() == direction::SOUTH) * (boatSize - 1)));
            tempBattleShip.setBasePosition((int8_t)tempX(engine), (int8_t)tempY(engine));

            /**Detects if a boat collide with another**/
            isColliding = doesBoatCollide(tempBattleShip);

            /*Debug Purpose only*/
            tempBattleShip.printBoat();
            printVector(tempBattleShip.placeBoat());
            if (isColliding) {
                std::cout << "Colliding ! Recalculating..." << std::endl;
            }
        } while (isColliding);

        /**We update the vector of boats inside the object**/
        m_battleships.push_back(tempBattleShip);
    }
}

bool board::doesBoatCollide(battleship ship)
{
    /**position of the boat to test**/
    std::vector<position> shipPos = ship.placeBoat();
    /**For each ship in the object, we will get the positions of the boat**/
    for (auto testShips : m_battleships) {
        std::vector<position> testShipPos = testShips.placeBoat();
        /**NOT OPTIMISED AT ALL
         * Will test each position with all the past boats. -> Could be better in term of pure syntax, as well as algorithm
         * -> Maybe use a std fonction ?**/
        for (auto testPositions : testShipPos) {
            for (auto positions : shipPos) {
                /**WE ONLY RETURN TRUE IF THIS HAPPENS ONE TIME**/
                if ((positions.x == testPositions.x) && (positions.y == testPositions.y)) {
                    return true;
                }
            }
        }
    }
    /**Return false otherwise.l**/
    return false;
}

/**     ---     BOATS       ---      **/

battleship::battleship(uint8_t size, direction orientation)
    : m_size(size)
    , m_orientation(orientation)
{
}

void battleship::setBasePosition(int8_t x, int8_t y)
{
    m_position = { x, y };
}

void battleship::printBoat()
{
    std::cout << "Size :" << (int)m_size << "\tOrientation: " << direction2string(m_orientation) << "\t x=" << (int)m_position.x << "\t y=" << (int)m_position.y << std::endl;
}

position battleship::positionOperatorFromOrientation(direction orientation, bool noNegative, bool noPositive)
{
    position returnPos { 0, 0 };
    /**In the case of a true value for each one, will return null, if false it will return either a minus or a positive value**/
    int8_t negValue = noNegative ? 0 : -1;
    int8_t posValue = noPositive ? 0 : 1;
    /**Like a compass, for any given direction, we could increment or decrement a given axis. We return these axis.**/
    switch (orientation) {
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
    for (int8_t i = 0; i < m_size; i++) {
        /**We get the operator (+ or -) for the given orientation**/
        operatorPosition = positionOperatorFromOrientation(m_orientation);
        /**The position is determined with the given orientation, at any given position the x or y axis should increment or decrement by i factor.**/
        returnVector.push_back({ static_cast<int8_t>(m_position.x + ((operatorPosition.x) * i)), static_cast<int8_t>(m_position.y + ((operatorPosition.y) * i)) });
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
    /**For every position print the x and y axis.**/
    for (auto value : vector) {
        std::cout << "x =" << (int)value.x << ", y =" << (int)value.y << "\t";
    }
    std::cout << std::endl;
}

const char* direction2string(direction orientation)
{
    /**NOT OPTIMISED, CAN BE USED WITH AN STD::MAP, SOON TO CHANGE**/
    switch (orientation) {
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