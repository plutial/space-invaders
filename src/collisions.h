#pragma once

#include "entity.h"
#include "bullet.h"
#include "enemy.h"

void UpdateCollisions(struct Entity *player, struct BulletArray *bullets, struct Army *army);
