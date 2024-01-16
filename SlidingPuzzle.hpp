#include "GeneralHeader.hpp"
#include "Entity.hpp"
#include "raylib.h"

void walls(vector<Entity> entity)
{
    vector<Entity> entities = {Entity({0, 0, 150, 250}, 0, BLUE)};

}

bool mainSlidingPuzzle()// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    // Gameplay loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();

    }
    
    return false;
}
