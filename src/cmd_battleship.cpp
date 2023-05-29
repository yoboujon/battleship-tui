#include "cmd_battleship.h"

using namespace battleshiptui;

commandBattleship::commandBattleship()
{
}

commandBattleship::~commandBattleship()
{
}

void commandBattleship::readCommand(std::string cmd)
{
    m_cmd = cmd;
    auto args=parser();
    for (auto & arg : args) 
    {
        if(arg == args[0])
        std::cout << "Command entered: " << arg << "\nArguments: ";
        else
        std::cout << "'" << arg << "'\t";
    }
    std::cout << std::endl;
}