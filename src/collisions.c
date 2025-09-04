#include "collisions.h"

#include "body.h"
#include <math.h>

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

bool UpdateTileCollisions(struct BulletArray *bullets, int bullet_index, struct TileArray *tiles)
{
    // Check collsions for each tile
    for (int i = 0; i < tiles->capacity; i++)
    {
        if (tiles->exists[i])
        {
            bool collision = BodyCollisions(bullets->bullets[bullet_index].body, tiles->tiles[i].body);

            // If they collided, set both to dead
            if (collision)
            {
                bullets->exists[bullet_index] = false;

                // Decrease the tile's health
                tiles->tiles[i].health -= 1;

                return true;
            }
        }
    }

    return false;
}

bool UpdateEnemyCollisions(struct BulletArray *bullets, int bullet_index, struct Army *army, int *score)
{
    // Check that the enemy owns the bullet
    if (bullets->bullets[bullet_index].owner)
    {
        return false;
    }

    for (int i = 0; i < army->length; i++)
    {
        if (army->exists[i])
        {
            bool collision = BodyCollisions(bullets->bullets[bullet_index].body, army->enemies[i].body);
 
            // If they collided, set both to dead
            if (collision)
            {
                bullets->exists[bullet_index] = false;

                army->alive -= 1;
                army->exists[i] = false;

                // Update the score
                int type = floorf((float) i / army->width);

                switch (type)
                {
                    case 0:
                        *score += 40;
                        break;

                    case 1:
                    case 2:
                        *score += 20;
                        break;

                    case 3:
                    case 4:
                        *score += 10;
                        break;

                    default:
                        break;
                }

                return true;
            }
        }
    }

    return false;
}

// Update bullet collisions
void UpdateCollisions(struct Entity *player, struct Army *army, struct BulletArray *bullets, struct TileArray *tiles, bool *lose, int *score)
{
    for (int i = 0; i < bullets->capacity; i++)
    {
        if (bullets->exists[i])
        {
            bool collision = UpdateTileCollisions(bullets, i, tiles);

            if (collision)
            {
                continue;
            }


            // If the player owns the bullet
            if (!bullets->bullets[i].owner)
            {
                collision = UpdateEnemyCollisions(bullets, i, army, score);

                if (collision)
                {
                    continue;
                }
            }
            // If the player owns the bullet
            else
            {
                bool collision = BodyCollisions(bullets->bullets[i].body, player->body);

                // If the player gets hit by an enemy bullet, the player loses
                if (collision)
                {
                    *lose = true;
                }
            }
        }
    }
}
