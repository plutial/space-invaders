#pragma once

#include "entity.h"
#include "enemy.h"
#include "bullet.h"
#include "tile.h"

void UpdateCollisions(struct Entity *player, struct Army *army, struct BulletArray *bullets, struct TileArray *tiles, bool *lose, int *score);
