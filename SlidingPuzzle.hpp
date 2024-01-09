#include "GeneralHeader.hpp"

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