#pragma once

#include "entity.h"
#include "bullet.h"

struct Entity NewPlayer();
void MovePlayer(struct Entity *player);
void UpdatePlayer(struct Entity *player);
void PlayerAttack(struct Entity player, struct BulletArray *bullets);
