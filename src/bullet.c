#include "bullet.h"
#include "raylib.h"
#include "sprite.h"

// Bullet texture
Texture2D bullet_texture;

struct Bullet NewBullet()
{
    // Load the bullet texture
    if (!IsTextureValid(bullet_texture))
    {
        bullet_texture = LoadTexture("assets/bullet.png");
    }

    // Create the sprite with the bullet texture
    struct Sprite sprite = NewSprite(bullet_texture);

    sprite.src_rect = (Rectangle) {0, 0, 16, 16};
    sprite.dst_rect = (Rectangle) {0, 0, 16, 16};

    // Initialize a default body to modify later
    struct Body body;
    body.size.x = sprite.dst_rect.width;
    body.size.y = sprite.dst_rect.height;

    // Create the bullet
    struct Bullet bullet = {
        .sprite = sprite,
        .body = body
    };

    return bullet;
}

struct BulletArray NewBulletArray()
{
    struct BulletArray array;

    array.capacity = 100;

    // Reset the arrays
    for (int i = 0; i < array.capacity; i++)
    {
        array.bullets[i] = (struct Bullet) {};
        array.exists[i] = false;
    }

    return array;
}

void AddBullet(struct BulletArray *array, struct Bullet bullet)
{
    // If the array is full, don't add the bullet
    for (int i = 0; i < array->capacity; i++)
    {
        // Check for an empty space
        if (!array->exists[i])
        {
            array->bullets[i] = bullet;
            array->exists[i] = true;

            // Stop here
            return;
        }
    }
}

void UpdateBullets(struct BulletArray *array)
{
    for (int i = 0; i < array->capacity; i++)
    {
        if (array->exists[i])
        {
            // Move the body up
            float speed = 3.0f;
            array->bullets[i].body.position.y -= speed;

            // Update the position of the sprite
            array->bullets[i].sprite.dst_rect.x = array->bullets[i].body.position.x;
            array->bullets[i].sprite.dst_rect.y = array->bullets[i].body.position.y;

            // Remove the bullet if the bullet leaves the screen
            if (array->bullets[i].body.position.y + array->bullets[i].body.size.y < 0)
            {
                array->exists[i] = false;
            }
        }
    }
}


void RenderBullets(struct BulletArray *array)
{
    for (int i = 0; i < array->capacity; i++)
    {
        if (array->exists[i])
        {
            RenderSprite(array->bullets[i].sprite);
        }
    }
}
