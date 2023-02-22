#include "Player.h"

void Player::Update(float hScreen, SDL_FRect& rect)
{
    if ((position.y > 0) && (position.y < hScreen - position.h))
    {
        rect = position;
        position.y += dy;
    }
    if (position.y <= 0)
        position.y = 1;

    if (position.y >= hScreen - position.h)
        position.y = hScreen - position.h - 1;
}
void Player::Movement(SDL_Event& e, Player& playerLeft, Player& playerRight)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_s)
        {
            playerLeft.dy = 0.5;
        }

        if (e.key.keysym.sym == SDLK_w)
        {
            playerLeft.dy = -0.5;
        }

        if (e.key.keysym.sym == SDLK_DOWN)
        {
            playerRight.dy = 0.5;
        }
        if (e.key.keysym.sym == SDLK_UP)
        {
            playerRight.dy = -0.5;
        }
    }

    if (e.type == SDL_KEYUP)
    {
        if (e.key.keysym.sym == SDLK_s)
            playerLeft.dy = 0;
        if (e.key.keysym.sym == SDLK_w)
            playerLeft.dy = 0;
        if (e.key.keysym.sym == SDLK_DOWN)
            playerRight.dy = 0;
        if (e.key.keysym.sym == SDLK_UP)
            playerRight.dy = 0;
    }
}
void Player::Movement(SDL_Event& e, Player& playerLeft)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_s)
        {
            playerLeft.dy = 0.5;
        }

        if (e.key.keysym.sym == SDLK_w)
        {

            playerLeft.dy = -0.5;
        }
    }

    if (e.type == SDL_KEYUP)
    {
        if (e.key.keysym.sym == SDLK_s)
            playerLeft.dy = 0;
        if (e.key.keysym.sym == SDLK_w)
            playerLeft.dy = 0;
    }
}