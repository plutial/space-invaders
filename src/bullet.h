#pragma once

#include "body.h"
#include "sprite.h"

struct Bullet
{
    struct Body body;
    struct Sprite sprite;

    // false -> the player owns the bullet
    // true  -> the enemy owns the bullet
    bool owner;
};

struct BulletArray
{
    // Default capacity is 100
    struct Bullet bullets[100];

    // Meta data
    int capacity;
    bool exists[100];
};

struct Bullet NewBullet();
struct BulletArray NewBulletArray();
void AddBullet(struct BulletArray *array, struct Bullet bullet);
void UpdateBullets(struct BulletArray *array);
void RenderBullets(struct BulletArray *array);
