#include "sprite.h"
#include "raylib.h"

struct Sprite NewSprite(Texture2D texture)
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

    // Scale the sprite to the window size
    Vector2 original_window_size = {800, 450};

    Vector2 window_scale = {0, 0};
    window_scale.x = (float) GetScreenWidth() / original_window_size.x;
    window_scale.y = (float) GetScreenHeight() / original_window_size.y;

    sprite.dst_rect.x *= window_scale.x;
    sprite.dst_rect.width *= window_scale.x;

    sprite.dst_rect.y *= window_scale.y;
    sprite.dst_rect.height *= window_scale.y;

    // Scale the sprite
    Vector2 scale = {2, 2};
    
    sprite.dst_rect.x *= scale.x;
    sprite.dst_rect.width *= scale.x;

    sprite.dst_rect.y *= scale.y;
    sprite.dst_rect.height *= scale.y;

    DrawTexturePro(sprite.texture, sprite.src_rect, sprite.dst_rect, 
                   origin, rotation, color);
}
