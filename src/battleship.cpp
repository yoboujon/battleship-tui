#include "battleship.h"
#include "exception.h"
#include <algorithm>
#include <cstring>
#include <string>

using namespace battleshiptui;

/*------------------------------------------------------*/
/*                          Board                       */
/*------------------------------------------------------*/

board::board()
    : board(LENGTH_BASE, LENGTH_BASE)
{
}

board::board(loglevel log)
    : board(LENGTH_BASE, LENGTH_BASE, log)
{
}

board::board(uint16_t width, uint16_t height, loglevel log)
    : m_log(log)
    , m_width(width)
    , m_height(height)
    , m_gameFinished(false)
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
    std::mt19937 engine(seeder());
    bool isColliding(false);

    /**First check if all the boats can fit in the grid**/
    if ((m_height * m_width) < std::accumulate(boatsNumber.begin(), boatsNumber.end(), 0))
        throw battleshipException(1, "Too much boats for the grid !");
    /**Check if the size of width/height can contain the biggest boat**/
    auto maxSizeBoat = *std::max_element(boatsNumber.begin(), boatsNumber.end());
    if ((maxSizeBoat > m_height) || (maxSizeBoat > m_width))
        throw battleshipException(2, std::string("The grid has a size of " + std::to_string(m_height) + "x" + std::to_string(m_width) + ", the biggest boat has a size of " + std::to_string(maxSizeBoat)));
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

            if (m_log == loglevel::DEBUG) {
                tempBattleShip.printBoat();
                printVector(tempBattleShip.getBoatPositions());
                if (isColliding)
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
    std::vector<position> shipPos = ship.getBoatPositions();
    /**For each ship in the object, we will get the positions of the boat**/
    for (auto testShips : m_battleships) {
        auto testShipPos = testShips.getBoatPositions();
        /** NOT OPTIMISED
         * ! Will test each position with all the past boats. -> Could be better in term of pure syntax, as well as algorithm
         * TODO : -> Maybe use a std fonction ?**/
        for (auto testPositions : testShipPos) {
            for (auto positions : shipPos) {
                /**WE ONLY RETURN TRUE IF THIS HAPPENS ONE TIME**/
                if ((positions.x == testPositions.x) && (positions.y == testPositions.y)) {
                    return true;
                }
            }
        }
    }
    /**Return false otherwise**/
    return false;
}

boatStatus board::attack(position pos)
{
    // We inform in debug where the attack is launched
    if (m_log == loglevel::DEBUG)
        std::cout << "Launched an attack at x:" << int(pos.x) << ", y:" << int(pos.y) << std::endl;
    // We iterate through all the boats to find if the position correponds to one of them
    for (auto& boat : m_battleships) {
        for (auto& boatPositions : boat.getBoatPositions()) {
            if ((pos.x == boatPositions.x) && (pos.y == boatPositions.y))
                return boat.hitBoat(pos);
        }
    }
    // If no boat found then we return the SPLASHWATER status
    return boatStatus::SPLASHWATER;
}

bool board::isGameFinished(void)
{
    return m_gameFinished;
}

/*------------------------------------------------------*/
/*                    Battleship                        */
/*------------------------------------------------------*/

battleship::battleship(uint8_t size, direction orientation)
    : m_size(size)
    , m_orientation(orientation)
{
    m_hitCount.reserve(size);
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

std::vector<position> battleship::getBoatPositions()
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

boatStatus battleship::hitBoat(position pos)
{
    // We first verify if all the position of the boat has already been hit
    if (m_hitCount.size() >= m_size)
        return boatStatus::SUNK;
    // Then we verify if the position given corresponds to a position of the hit count
    for (auto& boatHit : m_hitCount) {
        if ((boatHit.x == pos.x) && (boatHit.y == pos.y))
            return  boatStatus::SPLASHBOAT;
    }
    // If not we add the position to the hit count
    m_hitCount.push_back(pos);
    // We then verify, if we don't hit the boat, that the boat is sinking or not.
    return m_hitCount.size() >= m_size ? boatStatus::SUNK : boatStatus::HIT;
}

/*------------------------------------------------------*/
/*                    Base Functions                    *
!   May be placed in a separate library later.          */
/*------------------------------------------------------*/

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