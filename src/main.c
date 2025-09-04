#include <raylib.h>
#include <stdio.h>

#include "bullet.h"
#include "collisions.h"
#include "enemy.h"
#include "player.h"
#include "tile.h"

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // Create the window
    InitWindow(800, 450, "Space Invaders");
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // Target FPS
    SetTargetFPS(60);

    struct Entity player = NewPlayer();
    struct Army army = NewArmy();
    struct BulletArray bullets = NewBulletArray();
    struct TileArray tiles = NewTileArray();

    int round = 0;
    int score = 0;
    int high_score = 0;

    bool win = false;
    bool lose = false;
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // If the player has won the game
        if (win)
        {
            win = false;

            // Go to the next round
            round += 1;

            // Reset all entities
            player = NewPlayer();
            army = NewArmy();
            bullets = NewBulletArray();
            tiles = NewTileArray();

            // Increase the difficulty
            army.max_delay -= round * 5;
        }
        // If the game has not been lost
        else if (!lose)
        {
            // Update
            MovePlayer(&player);
            PlayerAttack(player, &bullets);

            ArmyAttack(&army, &bullets);

            // Update all entities
            UpdatePlayer(&player);
            UpdateArmy(&army, &win, &lose);
            UpdateBullets(&bullets);
            UpdateTiles(&tiles);

            // Handle bullet collisions
            UpdateCollisions(&player, &army, &bullets, &tiles, &lose, &score);
        }
        // Restart the game
        else if (lose && IsKeyPressed(KEY_SPACE))
        {
            win = false;
            lose = false;

            // Reset the round
            round = 0;

            // Reset the score
            score = 0;
        }
        else if (lose)
        { 
            // Reset all entities
            player = NewPlayer();
            army = NewArmy();
            bullets = NewBulletArray();
            tiles = NewTileArray();

            // MovePlayer(&player);
            // PlayerAttack(player, &bullets);

            // ArmyAttack(&army, &bullets);

            // Update all entities
            UpdatePlayer(&player);
            // UpdateArmy(&army, &lose);
            // UpdateBullets(&bullets);
            UpdateTiles(&tiles);

        }

        // Update the score
        if (score > high_score)
        {
            high_score = score;
        }

        // Draw
        BeginDrawing();

        // Clear the screen
        ClearBackground(BLACK);

        RenderSprite(player.sprite);
        RenderArmy(&army);
        RenderBullets(&bullets);
        RenderTiles(&tiles);

        Vector2 original_window_size = {800, 450};

        Vector2 window_scale = {0, 0};
        window_scale.x = (float) GetScreenWidth() / original_window_size.x;
        window_scale.y = (float) GetScreenHeight() / original_window_size.y;

        // Score
        char message[1000];
        sprintf(message, "Score: %d", score);
        DrawText(message, 
                 10 * window_scale.x, 420 * window_scale.y, 
                 20 * window_scale.x, LIGHTGRAY);

        
        // Lose message
        if (lose)
        {
            DrawText("You lose! Press [Space] to try again.", 
                     220 * window_scale.x, 190 * window_scale.y, 
                     20 * window_scale.x, LIGHTGRAY);

            // Score
            DrawText("Score", 
                     330 * window_scale.x, 220 * window_scale.y, 
                     20 * window_scale.x, LIGHTGRAY);

            sprintf(message, "%d", score);
            DrawText(message, 
                     450 * window_scale.x, 220 * window_scale.y, 
                     20 * window_scale.x, LIGHTGRAY);


            // High score
            DrawText("High Score", 
                     330 * window_scale.x, 240 * window_scale.y, 
                     20 * window_scale.x, LIGHTGRAY);

            sprintf(message, "%d", high_score);
            DrawText(message, 
                     450 * window_scale.x, 240 * window_scale.y, 
                     20 * window_scale.x, LIGHTGRAY);


        }

        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}
