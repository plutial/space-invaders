#include "tile.h"
#include "raylib.h"
#include "sprite.h"

Texture2D tile_texture;

struct Tile NewTile()
{
    // Create the enemy texture
    if (!IsTextureValid(tile_texture))
    {
        tile_texture = LoadTexture("assets/tile.png");
    }

    struct Tile tile;

    // By default, the tile is not a corner
    tile.isCorner = false;
    tile.isLeft = false;

    // The tile has four health
    // When it reaches zero, it dies
    tile.health = 4;

    tile.sprite = NewSprite(tile_texture);
    tile.sprite.src_rect = (Rectangle) {0, 0, 8, 8};
    tile.sprite.dst_rect = (Rectangle) {0, 0, 8, 8};

    tile.body.position = (Vector2) {0, 0};
    tile.body.size = (Vector2) {8, 8};

    return tile;
}

struct TileArray NewTileArray()
{
    struct TileArray tiles;

    tiles.capacity = 20;

    // Reset the tiles
    for (int i = 0; i < 4; i++)
    {
        // Update the sprite
        for (int j = 0; j < 5; j++)
        {
            tiles.tiles[i * 5 + j] = NewTile();

            tiles.exists[i * 5 + j] = true;

            // Shift the position of the tiles
            Vector2 shift = {16 * 1 + i * 16 * 7, 16 * 11 + 8};

            int type = j % 5;
            switch (type)
            {
                // Top left corner
                case 0:
                    tiles.tiles[i * 5 + j].body.position.x = shift.x + 0;
                    tiles.tiles[i * 5 + j].body.position.y = shift.y + 0;

                    tiles.tiles[i * 5 + j].isCorner = true;
                    tiles.tiles[i * 5 + j].isLeft = true;

                    break;

                // Top middle
                case 1:
                    tiles.tiles[i * 5 + j].body.position.x = shift.x + 8;
                    tiles.tiles[i * 5 + j].body.position.y = shift.y + 0;

                    break;

                // Top right corner
                case 2:
                    tiles.tiles[i * 5 + j].body.position.x = shift.x + 16;
                    tiles.tiles[i * 5 + j].body.position.y = shift.y + 0;

                    tiles.tiles[i * 5 + j].isCorner = true;
                    tiles.tiles[i * 5 + j].isLeft = false;

                    break;

                // Bottom left
                case 3:
                    tiles.tiles[i * 5 + j].body.position.x = shift.x + 0;
                    tiles.tiles[i * 5 + j].body.position.y = shift.y + 8;

                    break;

                // Bottom right
                case 4:
                    tiles.tiles[i * 5 + j].body.position.x = shift.x + 16;
                    tiles.tiles[i * 5 + j].body.position.y = shift.y + 8;

                    break;

                default:
                    break;
            }
        }
    }

    return tiles;
}

void UpdateTiles(struct TileArray *tiles)
{
    for (int i = 0; i < tiles->capacity; i++)
    {
        if (tiles->exists[i])
        {
            // Update the position
            tiles->tiles[i].sprite.dst_rect.x = tiles->tiles[i].body.position.x;
            tiles->tiles[i].sprite.dst_rect.y = tiles->tiles[i].body.position.y;

            // Update the sprite based on the health
            switch (tiles->tiles[i].health)
            {
                case 4:
                    if (tiles->tiles[i].isCorner)
                    {
                        if (tiles->tiles[i].isLeft)
                        {
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {16, 0, 8, 8};
                        }
                        else
                    {
                            // The negative width flips the texture on the x-axis
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {16, 0, -8, 8};
                        }
                    }
                    else
                {
                        tiles->tiles[i].sprite.src_rect = (Rectangle) {0, 0, 8, 8};
                    }
                    break;

                case 3:
                    if (tiles->tiles[i].isCorner)
                    {
                        if (tiles->tiles[i].isLeft)
                        {
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {24, 0, 8, 8};
                        }
                        else
                    {
                            // The negative width flips the texture on the x-axis
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {24, 0, -8, 8};
                        }
                    }
                    else
                {
                        tiles->tiles[i].sprite.src_rect = (Rectangle) {8, 0, 8, 8};
                    }
                    break;

                case 2:
                    if (tiles->tiles[i].isCorner)
                    {
                        if (tiles->tiles[i].isLeft)
                        {
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {16, 8, 8, 8};
                        }
                        else
                    {
                            // The negative width flips the texture on the x-axis
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {16, 8, -8, 8};
                        }
                    }
                    else
                {
                        tiles->tiles[i].sprite.src_rect = (Rectangle) {0, 8, 8, 8};
                    }
                    break;

                case 1:
                    if (tiles->tiles[i].isCorner)
                    {
                        if (tiles->tiles[i].isLeft)
                        {
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {24, 8, 8, 8};
                        }
                        else
                    {
                            // The negative width flips the texture on the x-axis
                            tiles->tiles[i].sprite.src_rect = (Rectangle) {24, 8, -8, 8};
                        }
                    }
                    else
                {
                        tiles->tiles[i].sprite.src_rect = (Rectangle) {8, 8, 8, 8};
                    }
                    break;

                // If the tile has no health, set its status to dead
                case 0:
                    tiles->exists[i] = false;

                    break;


                default:
                    // Default texture
                    tiles->tiles[i].sprite.src_rect = (Rectangle) {0, 0, 8, 8};
                    break;
            }        
        }
    }
}

void RenderTiles(struct TileArray *tiles)
{
    for (int i = 0; i < tiles->capacity; i++)
    {
        if (tiles->exists[i])
        {
            RenderSprite(tiles->tiles[i].sprite);
        }
    }
}
