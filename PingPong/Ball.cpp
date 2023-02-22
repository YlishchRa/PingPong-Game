#include "Ball.h"

void Ball::Update(SDL_FRect& rect, float hScreen, float wScreen, const SDL_FRect& playerLeftRect, const SDL_FRect& playerRightRect,
                  int* socreLeft, int* scoreRight)
{

    if (position.x <= 0)
    {
        ++*scoreRight;
        cout << "Right player`s score: " << *scoreRight << endl;
        ballSkiped = true;
    }
    else if (position.x >= wScreen - h)
    {
        ++*socreLeft;
        ++*socreLeft;
        cout << "Left player`s score: " << *socreLeft << endl;
        ballSkiped = true;
    }

    if (SDL_HasIntersectionF(&playerLeftRect, &rect))
    {
        if (dy == 0)
        {
            dy = -0.25;
        }
        dx = dx + priscor;
        dy = dy + priscor;
        dx *= -1;
    }
    else if (SDL_HasIntersectionF(&playerRightRect, &rect))
    {
        if (dy == 0)
        {
            dx = -0.25;
        }
        dx = dx + priscor;
        dy = dy + priscor;
        dx *= -1;
    }

    if (position.y >= hScreen - h)
    {
        if (dx == 0)
        {
            dx = -0.25;
        }
        dy *= -1;
    }
    else if (position.y <= 0)
    {
        if (dx == 0)
        {
            dx = 0.25;
        }
        dy *= -1;
    }

    position.x += dx;
    position.y += dy;

    rect = position;
}
bool Ball::GetBallSkiped()
{
    return ballSkiped;
}
void Ball::SetBallSkiped(bool balls)
{
    ballSkiped = balls;
}
