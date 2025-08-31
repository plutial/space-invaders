#pragma once

#include <raylib.h>

struct Sprite
{
    Texture2D texture;

    // Source and destination
    Rectangle src_rect, dst_rect;
};

struct Sprite NewSprite(Texture2D texture);
void RenderSprite(struct Sprite sprite);
