#include "Platformer.hpp"
#include "Breakout.hpp"
#include "SlidingPuzzle.hpp"
#include "time.h"

int main()
{
    vector<Brick> bricks;
    
    InitWindow(1000, 600, "Placeholder");
    
    srand(time(NULL));
    
    SetTargetFPS(60);
    
    if(!mainSlidingPuzzle()) return 0;
    if(!mainBreakout(bricks)) return 0;
    mainPlatformer(bricks);
}