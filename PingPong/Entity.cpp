#include "Entity.h"

void Entity::LoadMedia(SDL_Renderer* gRenderer)
{
    // Loading success flag
    bool success = true;

    SDL_Surface* loadedTexture = IMG_Load(path.c_str());

    if (loadedTexture == nullptr)
    {
        printf("Failed to load texture image!\n");
        success = false;
    }
    else
    {
        img = SDL_CreateTextureFromSurface(gRenderer, loadedTexture);
        if (img == nullptr)
        {
            std::cout << "Error text\n" << IMG_GetError();
        }

        SDL_FreeSurface(loadedTexture);
    }
    cout << "Seccess" << endl;
}
void Entity::SetDx(float _dx)
{
    dx = _dx;
}
void Entity::SetDy(float _dy)
{
    dy = _dy;
}
void Entity::SetRect(const SDL_FRect& rect)
{
    position.x = rect.x;
    position.y = rect.y;
}
void Entity::SetPosition(const SDL_FRect& _rect)
{
    position.x = _rect.x;
    position.y = _rect.y;
}

float Entity::GetDy()
{
    return dy;
}

float Entity::GetDx()
{
    return dx;
}
SDL_FRect Entity::GetRect()
{
    return position;
}
SDL_Texture* Entity::GetTexure()
{
    return img;
}