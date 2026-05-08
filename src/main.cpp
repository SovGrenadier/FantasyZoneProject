/*
Fantasy Zone (https://github.com/SovGrenadier/FantasyZoneProject)
Date: 5/08/2025
Desc: This is a recreation of the Arcade Game Fantasy Zone

XML Documentation:
.../FantasyZoneProject/x64/Debug/FantasyZoneProject.xml

Credits and statement of integrity:
.../FantasyZoneProject/src/Credits.txt

(Menu)
Z - Add credit
X - Player one button
I - Give Player Invisibility
B - Give Player Slow Bullets
N - Stop enemy spawn rate from speeding up

(Ingame)
UP Arrow - Move up
Right Arrow - Move right
Left Arrow - Move left
DOWN Arrow - Move down
X - Shoot
Z - Drop Bomb

What needs work:
- Other levels
- UI needs finished/polishing
- Bosses
- Player movement
- Coin system
- Player will just teleport into the void sometimes likely due to 
issue with the viewport loop
- Game sound; we didn't find any viable files to use

*/

#include <SFML/Graphics.hpp>
#include"../../src/Game/Game.h"
#include<iostream>

int main()
{
    Game game;
    game.run();
    return 0;
}
