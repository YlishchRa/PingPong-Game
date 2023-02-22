#include "FTexture.h"

void FTexture::NewScore(int* score, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font)
{
    font = TTF_OpenFont(path.c_str(), 1500);
    stringstream scoreToInt;
    scoreToInt << *score;
    string scoreSRT = " ";
    scoreToInt >> scoreSRT;
    loadFromRenderedText(scoreSRT, textColor, renderer, font);
}
bool FTexture::loadMedia(TTF_Font* font, string path, SDL_Renderer* renderer)
{
    // Loading success flag
    bool success = true;

    // Open the font
    font = TTF_OpenFont(path.c_str(), 60);
    if (font == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    else
    {
        // Render text
        SDL_Color textColor = {0xff, 0xff, 0xff};
        if (!loadFromRenderedText("0", textColor, renderer, font))
        {
            printf("Failed to render text texture!\n");
            success = false;
        }
    }

    return success;
}

bool FTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font)
{

    SDL_Surface* textSurface = TTF_RenderText_Blended(font, textureText.c_str(), textColor);

    if (textSurface == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        scoreTexure = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (scoreTexure == NULL)
        {
            printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }
        else
        {
            // Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    // Render text surface

    // Return success
    return scoreTexure != NULL;
}

// Deallocates texture
void FTexture::free(TTF_Font* font)
{
    if (font != nullptr)
        TTF_CloseFont(font);
    font = nullptr;
}
// Gets image dimensions
int FTexture::getWidth()
{
    return mWidth;
}
int FTexture::getHeight()
{
    return mHeight;
}
SDL_Texture* FTexture::GetFontTexture()
{
    return scoreTexure;
}