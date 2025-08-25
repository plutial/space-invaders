#include "sprite.h"
#include "raylib.h"

struct Sprite CreateSprite(Texture2D texture)
{
    struct Sprite sprite;

    sprite.texture = texture;

    return sprite;
}

void RenderSprite(struct Sprite sprite)
{
    Vector2 origin = {0, 0};
    float rotation = 0;
    Color color = WHITE;
    DrawTexturePro(sprite.texture, sprite.src_rect, sprite.dst_rect, 
                   origin, rotation, color);
}
