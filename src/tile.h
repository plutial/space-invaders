#pragma once

#include "sprite.h"
#include "body.h"

struct Tile
{
    int health;
   
    // Whether the tile is a corner or not
    bool isCorner;

    // Whether the tile is a left corner, or a right corner
    bool isLeft;

    struct Sprite sprite;
    struct Body body;
};

struct TileArray
{
    // Default capacity is 20
    struct Tile tiles[20];

    // Meta data
    int capacity;
    bool exists[20];
};

struct Tile NewTile();
struct TileArray NewTileArray();
void UpdateTile(struct Tile *tile);
void UpdateTiles(struct TileArray *tiles);
void RenderTiles(struct TileArray *tiles);
