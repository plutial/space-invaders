#pragma once

#include "bullet.h"
#include "entity.h"

enum Direction
{
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_DOWN,
};

// An "army" is a bunch of enemies
// The 11 is the width, and 5 the height
struct Army
{
    struct Entity enemies[11 * 5];

    // Meta data
    // Stores the information on whether the enemy is alive
    bool exists[11 * 5];

    // Number of alive entities
    int alive;

    // Width and height
    // The length is the number of enemies
    int width, height, length;

    // Position
    Vector2 position;
    enum Direction direction;
};

struct Army NewArmy();
void UpdateArmy(struct Army *army);
void RenderArmy(struct Army *army);
void ArmyAttack(struct Army *army, struct BulletArray *array);
