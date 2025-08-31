#include "enemy.h"
#include "raylib.h"
#include "sprite.h"

#define MAX(a, b) (a) > (b) ? (a) : (b)

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

        struct Sprite sprite = NewSprite(enemy_texture);
        sprite.src_rect = (Rectangle) {0, 0, 16, 8};
        sprite.dst_rect = (Rectangle) {0, 0, 16, 8};

        struct Body body;
        body.position = (Vector2) {0, 8};
        body.position.x += (i % army.width) * 16;
        body.position.y += layer * 16;

        body.size = (Vector2) {16, 8};

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

    return army;
}

int delay = 0;
void UpdateArmy(struct Army *army)
{  
    for (int i = 0; i < army->length; i++)
    {
        if (army->exists[i])
        {
            army->enemies[i].sprite.dst_rect.x = army->enemies[i].body.position.x;
            army->enemies[i].sprite.dst_rect.y = army->enemies[i].body.position.y;

            if (delay == 0)
            {
                if (army->enemies[i].sprite.src_rect.x == 0)
                {
                    army->enemies[i].sprite.src_rect.x = 16;
                }
                else
                {
                    army->enemies[i].sprite.src_rect.x = 0;
                }
            }

        }
    }

    if (delay == 0)
    {
        delay = 30;
    }

    delay = MAX(0, delay - 1);
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
