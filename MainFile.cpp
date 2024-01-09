#include <stdlib.h>// For random number generator
#include "Platformer.hpp"
#include "Breakout.hpp"
#include "SlidingPuzzle.hpp"
#include "time.h"

int main()
{
    gameMode currentMode = slidingPuzzle;
    
    InitWindow(1000, 600, "Placeholder");
    
    srand(time(NULL));// We will probably need rng later on.
    
    SetTargetFPS(60);
    
    if(!mainSlidingPuzzle()) return 0;
    if(!mainBreakout()) return 0;
    mainPlatformer();
}