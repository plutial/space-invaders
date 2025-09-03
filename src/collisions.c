#include "collisions.h"

#include "body.h"

// Returns true if the bodies collided, and false for no collision
bool BodyCollisions(struct Body body_a, struct Body body_b)
{
    // Overlap in the x axis
    bool x_collision = body_a.position.x < body_b.position.x + body_b.size.x 
        && body_a.position.x + body_a.size.x > body_b.position.x;

    // Overlap in the y axis
    bool y_collision = body_a.position.y < body_b.position.y + body_b.size.y 
        && body_a.position.y + body_a.size.y > body_b.position.y;

    return x_collision && y_collision;
}

// Update bullet collisions
void UpdateCollisions(struct Entity *player, struct BulletArray *bullets, struct Army *army)
{
    for (int i = 0; i < bullets->capacity; i++)
    {
        if (bullets->exists[i])
        {
            // Check collision for each enemy
            for (int j = 0; j < army->length; j++)
            {
                if (army->exists[j])
                {
                    bool collision = BodyCollisions(bullets->bullets[i].body, army->enemies[j].body);

                    // If they collided, set both to dead
                    if (collision)
                    {
                        bullets->exists[i] = false;

                        army->alive -= 1;
                        army->exists[j] = false;

                        break;
                    }
                }
            }
        }
    }
}
