#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;
class Entity
{
  protected:
    float x, y, dx, dy, h;
    SDL_Texture* img;
    string path;
    SDL_FRect position;

  public:
    void LoadMedia(SDL_Renderer* gRenderer);
    void SetDx(float _dx);
    void SetDy(float _dy);
    void SetRect(const SDL_FRect& rect);
    void SetPosition(const SDL_FRect& _rect);

    SDL_FRect GetRect();
    SDL_Texture* GetTexure();
    float GetDx();
    float GetDy();
};
