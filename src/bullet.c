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
    struct BulletArray bullets;

    bullets.capacity = 100;

    // Reset the bulletss
    for (int i = 0; i < bullets.capacity; i++)
    {
        bullets.bullets[i] = (struct Bullet) {};
        bullets.exists[i] = false;
    }

    return bullets;
}

void AddBullet(struct BulletArray *bullets, struct Bullet bullet)
{
    // If the bullets is full, don't add the bullet
    for (int i = 0; i < bullets->capacity; i++)
    {
        // Check for an empty space
        if (!bullets->exists[i])
        {
            bullets->bullets[i] = bullet;
            bullets->exists[i] = true;

            // Stop here
            return;
        }
    }
}

void UpdateBullets(struct BulletArray *bullets)
{
    for (int i = 0; i < bullets->capacity; i++)
    {
        if (bullets->exists[i])
        {
            // Move the body up
            float speed = 3.0f;

            // If the player owns the bullet, go up to attack the enemy
            if (!bullets->bullets[i].owner)
            {
                bullets->bullets[i].body.position.y -= speed;
            }
            // If the enemy own the bullet, go down to attack the player
            else
            {
                bullets->bullets[i].body.position.y += speed;
            }

            // Update the position of the sprite
            bullets->bullets[i].sprite.dst_rect.x = bullets->bullets[i].body.position.x;
            bullets->bullets[i].sprite.dst_rect.y = bullets->bullets[i].body.position.y;

            // Remove the bullet if the bullet leaves the screen
            if (bullets->bullets[i].body.position.y + bullets->bullets[i].body.size.y < 0)
            {
                bullets->exists[i] = false;
            }
        }
    }
}


void RenderBullets(struct BulletArray *bullets)
{
    for (int i = 0; i < bullets->capacity; i++)
    {
        if (bullets->exists[i])
        {
            RenderSprite(bullets->bullets[i].sprite);
        }
    }
}
