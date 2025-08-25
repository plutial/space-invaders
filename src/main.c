#include <raylib.h>

int main(void)
{
    SetTraceLogLevel(LOG_WARNING);

    // Create the window
    InitWindow(800, 450, "Space Invaders");

    // Target FPS
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update

        // Draw
        BeginDrawing();

        // Clear the screen
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    // Close the window
    CloseWindow();

    return 0;
}
