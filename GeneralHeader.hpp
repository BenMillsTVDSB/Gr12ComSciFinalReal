#pragma once// check back later, remove if this is unneeded.

#include "raylib.h"

enum gameMode {slidingPuzzle, breakout, platformer};

void gameOverScreen()
{
    while(!WindowShouldClose())
    {
        BeginDrawing();
        EndDrawing();
    }
}