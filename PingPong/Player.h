#pragma once
#include "Entity.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

class Player : public Entity
{

  public:
    Player(float _x, float _y, float _dx, float _dy, float _h, string _path)
    {

        x = _x;
        y = _y;
        dx = _dx;
        dy = _dy;
        h = _h;
        path = _path;

        position.x = x;
        position.y = y;
        position.h = h + 70;
        position.w = h;
    }

    ~Player()
    {
        SDL_DestroyTexture(img);
    }

    void Update(float hScreen, SDL_FRect& rect);
    static void Movement(SDL_Event& e, Player& playerLeft, Player& playerRight);
    static void Movement(SDL_Event& e, Player& playerLeft);
};
