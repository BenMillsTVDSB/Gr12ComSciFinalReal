#include "GeneralHeader.hpp"
#include "raylib.h"


enum rectangle : char {left, right, up, down};

class Entity
{
    private:
        Rectangle hitbox; //= {x, y, width, height}
        float velocity;
        Color colour;

        //direction rectangleSlidingBlock(Rectangle otherhitBox, Vector2 otherVelocity)
        //{
            //otherhitBox.y -= otherVelocity.y * GetFrameTime();
            

            
        //}

    public:
        Rectangle getHitbox()
        {
            return hitbox;
        }

        void setHitbox (Rectangle newHitbox)
        {
            hitbox = newHitbox;
        }

        float velocity()
        {
            return velocity;
        }

        void setvelocity (float newVelocity)
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
            //storing rectangle components of entities
            int thisX = hitbox.x;
            int thisY = hitbox.y;
            int thisWidth = hitbox.width;
            int thisHeight = hitbox.height;

            int entityX = entity.getHitbox().x;
            int entityY = entity.getHitbox().y;
            int entityWidth = entity.getHitbox().width;
            int entityHeight = entity.getHitbox().height;

            if (entityWidth <= 0 || entityHeight <= 0 || thisWidth <= 0 || thisHeight <= 0)
            {
                return false;
            }

            // changing bounds
            entityWidth += entityX;
            entityHeight += entityY;
            thisWidth += thisX;
            thisHeight += thisY;

            //comparing bounds
            return ((entityWidth < entityX || entityWidth > thisX) && (entityHeight < entityY || entityHeight > thisY) && (thisWidth < thisX || thisWidth > entityX) && (thisHeight < thisY || thisHeight > entityY));
        }


        Entity (Rectangle newHitbox, float newVelocity, Color newColour)
        {
           hitbox = newHitbox; 
           velocity = newVelocity;
           colour = newColour;
        }
};
