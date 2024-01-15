#include "GeneralHeader.hpp"
#include "raylib.h"

bool mainSlidingPuzzle()// returns true if player clears section, false if they are defeated. Program ends upon returning false.
{
    // Gameplay loop
    while(!WindowShouldClose())
    {
        BeginDrawing();
        DrawRectangle(0,0,100,200, BLUE);



        EndDrawing();

    }
    
    return false;
}
