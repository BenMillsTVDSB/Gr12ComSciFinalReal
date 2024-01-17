#include "GeneralHeader.hpp"
#include "raylib.h"

class Entity
{
    private:
        Rectangle hitbox; //= {x, y, width, height}
        float velocity;
        Color colour;
        
    public:
        Rectangle getHitbox()
        {
            return hitbox;
        }

        void setHitbox (Rectangle newHitbox)
        {
            hitbox = newHitbox;
        }

        float getVelocity()
        {
            return velocity;
        }

        void setVelocity (float newVelocity)
        {
            velocity = newVelocity;
        }

        Color getColour()
        {
            return colour;
        }

        void setColour (Color newColour)
        {
            colour = newColour;
        }

        bool collidesWith(Entity entity) 
        {
            return CheckCollisionRecs(hitbox, entity.hitbox);
        }

        Entity (Rectangle newHitbox, float newVelocity, Color newColour)
        {
           hitbox = newHitbox; 
           velocity = newVelocity;
           colour = newColour;
        }
};
