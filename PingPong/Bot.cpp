#include "Bot.h"

void Bot::Update(Ball* ball, float wScreen, float hScreen, SDL_FRect& rectBot)
{

    if (position.y <= 0)
        position.y = 1;
    if (position.y >= hScreen - h)
        position.y = hScreen - h - 1;

    if (ball->GetDy() > 0)
    {
        dy = ball->GetDy() - 0.03;
    }
    else if (ball->GetDy() == 0)
    {
        dy = 0;
    }
    else
    {
        dy = ball->GetDy() + 0.03;
    }
    position.y += dy;

    rectBot = position;
}
