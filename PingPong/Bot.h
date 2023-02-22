#pragma once
#include "Ball.h"
#include "Entity.h"
class Bot : public Entity
{

  public:
    Bot(float _x, float _y, float _dx, float _dy, float _h, string _path)
    {

        x = _x;
        y = _y;
        dx = _dx;
        dy = _dy;
        h = _h + 70;
        path = _path;

        position.x = x;
        position.y = y;
        position.h = h;
        position.w = h - 70;
    }
    ~Bot()
    {
        SDL_DestroyTexture(img);
    }

    // Bots` brain
    void Update(Ball* ball, float wScreen, float hScreen, SDL_FRect& rectBot);
};
