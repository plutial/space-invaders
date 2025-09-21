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
void AddBullet(struct BulletArray *bullets, struct Bullet bullet);
void UpdateBullets(struct BulletArray *bullets);
void RenderBullets(struct BulletArray *bullets);
