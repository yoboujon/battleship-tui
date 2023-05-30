#ifndef HEADER_BTUI_BATTLESHIP
#define HEADER_BTUI_BATTLESHIP

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <numeric>
#include <random>
#include <cstdint>
#include <vector>


#define BASE_CHAR '.'
#define LENGTH_BASE 10

namespace battleshiptui {
/**
 * @brief set of direction, from NORTH to WEST.
 */
enum direction {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

/**
 * @brief loglevel for the battleship TUI
 */
enum class loglevel {
    NORMAL,
    DEBUG
};

/**
 * @brief position struct, only values between -128 and 128 (will maybe change later.)
 */
typedef struct {
    int8_t x;
    int8_t y;
} position;

class battleship {
private:
    /**
     * @brief the size will delimit the boat total position
     */
    uint8_t m_size;
    /**
     * @brief The direction will provide all the boat's position
     */
    direction m_orientation;
    /**
     * @brief works like a base position, the turning point for the boat.
     */
    position m_position;

public:
    battleship(uint8_t size, direction orientation);

    /**
     * @brief For any given orientation will return a position with a value modified only on the x or y axis.
     *
     * @param orientation the given direction
     * @param noNegative if true the position returned can't be negative, and will be replaced by a 0
     * @param noPositive if true the position returned can't be positive, and will be replaced by a 0
     * @return position NORTH -> -y, SOUTH -> +y, EAST -> +x, WEST -> -x
     */
    position positionOperatorFromOrientation(direction orientation, bool noNegative = false, bool noPositive = false);

    /**
     * @brief Set the base position of the battleship. The type choosen can be negative, but it is not recommended.
     *
     * @param x the position on the x axis
     * @param y the position on the y axis
     */
    void setBasePosition(int8_t x, int8_t y);

    /**
     * @brief For debug only, will print useful information about the given boat.
     */
    void printBoat();

    /**
     * @brief Get the direciton of the object.
     *
     * @return direction
     */
    direction getOrientation();

    /**
     * @brief Returns a vector of position of the battleship object.
     * With its given base position, will calculate the other coordonates in accordance
     * to his size and orientation.
     *
     * @return std::vector<position> vector of position in x and y.
     */
    std::vector<position> placeBoat();
};

class board {
private:
    loglevel m_log;
    char** m_board;
    uint16_t m_width;
    uint16_t m_height;
    std::vector<battleship> m_battleships;

    /**
     * @brief PROMPT TO HUGE UPDATE : NOT OPTIMISED
     *
     * @param ship a ship you want to test out
     * @return true if a boat collides with one of the object battleship.
     * @return false if there is no colliding.
     */
    bool doesBoatCollide(battleship ship);

public:
    /**
     * @brief Construct a new board object with the given LENGTH_BASE
     */
    board();
    board(loglevel log);
    /**
     * @brief Construct a new board object with a given width and height and a log level
     *
     * @param width     uint16_t
     * @param height    uint16_t
     * @param log       loglevel
     */
    board(uint16_t width, uint16_t height, loglevel log = loglevel::NORMAL);
    ~board();

    /**
     * @brief Prints out the m_board with the battle ships.
     * Shows every position that the user touched.
     *
     */
    void printBoard();

    /**
     * @brief Create multiple boat with a given vector of uint.
     * This function uses an algorithm to place the boats, then checks if the boats collide with each other.
     * TODO : - Detect if a given number of boat can be actually placed on a grid. (if totalsize of boat > totalsize of board.)
     *
     * @param boatsNumber  the size represents the number of boat, and each number is the boat's size.
     */
    void createBoats(std::vector<uint8_t> boatsNumber);

    /**
     * @brief Will deal damage to a boat if found at the given position
     *
     * @param pos
     */
    void attack(position pos);
};
};

/**
 * @brief ONLY FOR DEBUG PURPOSES
 * Print out a vector of position in this style : "x = , y = \t"
 *
 * @param vector vector of position struct.
 */
void printVector(std::vector<battleshiptui::position> vector);

/**
 * @brief converts a given direction enum to a string
 *
 * @param orientation direction
 * @return const char* char array of the direction
 */
const char* direction2string(battleshiptui::direction orientation);

#endif