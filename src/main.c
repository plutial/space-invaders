#include <raylib.h>

#include "bullet.h"
#include "collisions.h"
#include "enemy.h"
#include "player.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // Create the window
    InitWindow(800, 450, "Space Invaders");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Target FPS
    SetTargetFPS(60);

    struct Entity player = NewPlayer();
    struct BulletArray bullets = NewBulletArray();
    struct Army army = NewArmy();
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        MovePlayer(&player);
        PlayerAttack(player, &bullets);

        UpdateArmy(&army);
        ArmyAttack(&army, &bullets);

        UpdateBullets(&bullets);

        UpdateCollisions(&player, &bullets, &army);

        // Update sprite position
        player.sprite.dst_rect.x = player.body.position.x;
        player.sprite.dst_rect.y = player.body.position.y;

        // Draw
        BeginDrawing();

        // Clear the screen
        ClearBackground(BLACK);

        RenderSprite(player.sprite);
        RenderBullets(&bullets);
        RenderArmy(&army);

        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}
