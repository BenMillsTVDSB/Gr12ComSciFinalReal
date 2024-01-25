#include "Platformer.hpp"
#include "Breakout.hpp"
#include "SlidingPuzzle.hpp"

int main()// Ben.
{
    vector<Brick> bricks;
    clock_t startTime = -1;
    
    InitWindow(1000, 600, "Placeholder");
    
    srand(time(NULL));
    
    SetTargetFPS(60);
    
    if(!mainSlidingPuzzle(&startTime)) return 0;
    if(!mainBreakout(bricks)) return 0;
    mainPlatformer(bricks, startTime);
}