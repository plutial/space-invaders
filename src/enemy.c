#include "enemy.h"
#include "raylib.h"
#include "sprite.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)

#include <stdio.h>
#include <math.h>

Texture2D enemy_texture;

struct Army NewArmy()
{
    // Create the enemy texture
    if (!IsTextureValid(enemy_texture))
    {
        enemy_texture = LoadTexture("assets/enemy.png");
    }

    struct Army army;

    army.width = 11;
    army.height = 5;
    army.length = army.width * army.height;

    // There are 55 enemies alive at initialization
    army.alive = army.length;

    // Create the enemies
    for (int i = 0; i < army.length; i++)
    {
        // Layer
        int layer = (int) floorf((float) i / 11.0f);
  
        struct Body body;
        body.position = (Vector2) {0, 8};
        body.position.x += (i % army.width) * 16;
        body.position.y += layer * 16;

        body.size = (Vector2) {16, 8};

        struct Sprite sprite = NewSprite(enemy_texture);
        sprite.src_rect = (Rectangle) {0, 0, 16, 8};
        sprite.dst_rect = (Rectangle) {body.position.x, body.position.y, 16, 8};

        // Change the sprite for each layer
        switch (layer)
        {
            case 1:
            case 2:
                sprite.src_rect.y = sprite.src_rect.height * 1;
                break;

            case 3:
            case 4:
                sprite.src_rect.y = sprite.src_rect.height * 2;
                break;

            default:
                break;
                
        }

        army.enemies[i] = (struct Entity) {
            .sprite = sprite,
            .body = body
        };

        army.exists[i] = true;
    }

    // Moving the enemy
    army.position = (Vector2) {0, 0};
    
    // Start by going right
    army.direction = MOVE_RIGHT;

    return army;
}

#define MAX_DELAY 35
Vector2 delay = {MAX_DELAY, 1};
void UpdateArmy(struct Army *army)
{  
    // Only update when the delay is over
    if (delay.x != 0)
    {
        delay.x = MAX(0, delay.x - 1);
        return;
    } 
    else
    {
        // Reset the delay
        delay.x = MAX_DELAY;
    }

    for (int i = 0; i < army->length; i++)
    {
        if (army->exists[i])
        { 
            // Animation
            if (army->enemies[i].sprite.src_rect.x == 0)
            {
                army->enemies[i].sprite.src_rect.x = 16;
            }
            else
            {
                army->enemies[i].sprite.src_rect.x = 0;
            }

            // Move the enemies down
            if (army->direction == MOVE_DOWN)
            {
                army->enemies[i].body.position.y += 16;
            }
            // Move the enemies side to side
            else if (army->direction == MOVE_LEFT)
            {
                army->enemies[i].body.position.x -= 16;
            }
            else if (army->direction == MOVE_RIGHT)
            {
                army->enemies[i].body.position.x += 16;
            } 

            // Update the sprite
            army->enemies[i].sprite.dst_rect.x = army->enemies[i].body.position.x;
            army->enemies[i].sprite.dst_rect.y = army->enemies[i].body.position.y;
        }
    }

    // Move the enemies side to side
    if (army->direction == MOVE_LEFT)
    {
        army->position.x -= 1;
    }
    else if (army->direction == MOVE_RIGHT)
    {
        army->position.x += 1;
    }
 
    // Switch after 14 spaces
    int length = 14;

    if (((int) army->position.x) % length == 0)
    {
        delay.y -= 1;
    }

    // Move the enemies down
    if (delay.y == 0)
    {
        delay.y = 2;
        army->position.y += 0;
        army->direction = MOVE_DOWN;
    }
    // If the position is reaching the end, switch the direction
    else if (army->position.x == 0)
    {
        army->direction = MOVE_RIGHT;
    }
    else if (army->position.x == length)
    {
        army->direction = MOVE_LEFT;
    } 
    // Fail safe
    else if (army->direction == MOVE_DOWN)
    {
        army->direction = MOVE_RIGHT;
    } 
}

void RenderArmy(struct Army *army)
{
    for (int i = 0; i < army->length; i++)
    {
        if (army->exists[i])
        {
            RenderSprite(army->enemies[i].sprite);
        }
    }
}
