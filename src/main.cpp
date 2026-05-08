/*
Fantasy Zone (https://github.com/SovGrenadier/FantasyZoneProject)
Date: 5/08/2025
Desc: This is a recreation of the Arcade Game Fantasy Zone


Authors:
Hadeel A.
Darius W.
Azur M.
Philip C.

(Menu)
Z - Add credit
X - Player one button
I - Give Player Invinsibility

(Ingame)
UP Arrow - Move up
Right Arrow - Move right
Left Arrow - Move left
DOWN Arrow - Move down
X - Shoot
Z - Drop Bomb

What needs work:
- more animations
- enemy recolors/other enemies
- other levels
- UI needs finished/polishing
- obstacles
- Enemy ground collisions
- walls
- left side off map
- bullet collision
- bosses

We did not cheat.

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
