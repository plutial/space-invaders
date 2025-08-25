#pragma once

#include <raylib.h>

struct Sprite
{
    Texture2D texture;

    // Source and destination
    Rectangle src_rect, dst_rect;
};

struct Sprite CreateSprite(Texture2D texture);
void RenderSprite(struct Sprite sprite);
