#pragma once
#include "Entity.h"
#include "FTexture.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <iostream>

const int priscor = 0.00035;

using namespace std;

class Ball : public Entity
{
  public:
    bool ballSkiped;
    Ball(float _x, float _y, float _dx, float _dy, float _h, string _path)
    {
        x = _x;
        y = _y;
        dx = _dx;
        dy = _dy;
        h = _h;
        path = _path;

        position.x = x;
        position.y = y;
        position.h = h;
        position.w = h;
        ballSkiped = false;
        srand(time(0));
    }
    ~Ball()
    {
        SDL_DestroyTexture(img);
    }

    bool GetBallSkiped();
    void SetBallSkiped(bool ballS);
    // method update it is life of the object
    void Update(SDL_FRect& rect, float hScreen, float wScreen, const SDL_FRect& playerLeftRect, const SDL_FRect& playerRightRect,
                int* socreLeft, int* scoreRight);
};
