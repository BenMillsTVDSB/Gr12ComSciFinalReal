#include <string>
#include "GeneralHeader.hpp"
#include "raylib.h"

using namespace std;

class Entity
{
    private:
        Rectangle hitbox; //= {x, y, width, height}
        float velocity;
        Color colour;
        string type;
        
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

        string getType()
        {
            return type;
        }

        void setType (string newType)
        {
            type = newType;
        }

        bool collidesWith(Entity entity) 
        {
            return CheckCollisionRecs(hitbox, entity.hitbox);
        }

        Entity (Rectangle newHitbox, float newVelocity, Color newColour, string newType)
        {
           hitbox = newHitbox; 
           velocity = newVelocity;
           colour = newColour;
           type = newType;
        }

        virtual ~Entity() {}
};
