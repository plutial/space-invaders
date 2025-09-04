#include <raylib.h>

#define MAX(a, b) (a) > (b) ? (a) : (b)

#include "player.h"
#include "bullet.h"
#include "sprite.h"

struct Entity NewPlayer()
{
    struct Entity player;

    // The sprite scaling
    Vector2 scale = {2, 2};

    // Set the player's position to the middle of the window
    player.body.position = (Vector2) {(800 / scale.x - 16) / 2, 400 / scale.y};
    player.body.size = (Vector2) {16, 16};

    // Load the player texture
    Texture2D texture = LoadTexture("assets/player.png");
    player.sprite = NewSprite(texture);

    player.sprite.src_rect = (Rectangle) {0, 0, 16, 16};
    player.sprite.dst_rect = (Rectangle) {0, 0, 16, 16};

    return player;
}

void MovePlayer(struct Entity *player)
{
    float speed = 3.0f;

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
    {
        player->body.position.x -= speed;
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
    {
        player->body.position.x += speed;
    }

    // The sprite scaling
    Vector2 scale = {2, 2};

    // Limit the player from going out of bounds
    if (player->body.position.x <= 0)
    {
        player->body.position.x = 0;
    }
    else if (player->body.position.x >= 800 / scale.x - player->body.size.x)
    {
        player->body.position.x = 800 / scale.x  - player->body.size.x;
    }
}

void UpdatePlayer(struct Entity *player)
{
    // Update sprite position
    player->sprite.dst_rect.x = player->body.position.x;
    player->sprite.dst_rect.y = player->body.position.y;
}

int attack_delay = 0;
void PlayerAttack(struct Entity player, struct BulletArray *bullets)
{
    // The delay for each attack
    attack_delay = MAX(0, attack_delay - 1);

    bool attack = false;
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsKeyPressed(KEY_SPACE))
    {
        attack = true;
    }

    // Delay
    if (attack && attack_delay == 0)
    {
        struct Bullet bullet = NewBullet(); 
        bullet.body.position = player.body.position;

        AddBullet(bullets, bullet);

        // Start delay
        // The value is the number of frames
        // The game runs at 60 FPS
        attack_delay = 35;
    }
}
