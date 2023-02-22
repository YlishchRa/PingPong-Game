#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <sstream>

using namespace std;
class FTexture
{
  public:
    // Initializes variables
    FTexture(string path, SDL_Color textColor, SDL_Renderer* render, TTF_Font* font)
    {

        this->path = path;
        loadMedia(font, path, render);
    }

    // Gets image dimensions
    int getWidth();
    int getHeight();
    SDL_Texture* GetFontTexture();

    void NewScore(int* score, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font);
    bool loadMedia(TTF_Font* font, string path, SDL_Renderer* renderer);
    // Creates image from font string
    bool loadFromRenderedText(std::string textureText, SDL_Color textColor, SDL_Renderer* renderer, TTF_Font* font);
    // Deallocates texture
    void free(TTF_Font* font);

  private:
    // The actual hardware texture
    SDL_Texture* scoreTexure;
    string path;
    // Image dimensions
    int mWidth;
    int mHeight;
};
