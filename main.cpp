#include "read_file.h"
#include <iostream>

#include "Game.h"

int main()
{
    Game g("/home/rodrigo/Documents/Code/Cpp/GameDev/ECS/config.txt");
    g.run();

}
