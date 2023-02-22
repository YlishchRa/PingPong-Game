#include "Bot.h"
#include "Entity.h"
#include "FTexture.h"
#include "Player.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>

#undef main
using namespace std;

// Screen dimension constants
int imgFlags = IMG_INIT_PNG;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
int gScoreLeft = 0;
int gScoreRight = 0;

void RestartGame(Ball* ball, Player* paleyrLeft, Player* playerRight, FTexture* scoreLeft, FTexture* scoreRight);
void RestartGame(Ball* ball, Player* paleyrLeft, Bot* bot, FTexture* scoreLeft, FTexture* scoreRight);
bool init();                                                        // Starts up SDL
SDL_Texture* LoadBackground(string path, SDL_Texture* background);  // load background

void close();

// The window we'll be rendering to
SDL_Window* gWindow = NULL;
// The window renderer
SDL_Renderer* gRenderer = NULL;
// Background Image
SDL_Texture* background = nullptr;
SDL_FRect startRect{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0};
TTF_Font* gFont = nullptr;
SDL_Color color = {0xff, 0xff, 0xff};

int main(int argc, char* args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!TTF_WasInit())
            if (TTF_Init() == -1)
            {
                printf("SDL_ttf could not "
                       "initialize! "
                       "SDL_ttf Error: "
                       "%s\n",
                       TTF_GetError());
            }

        short botOrNot;
        bool withBot;

        cout << "Hello, it is simple "
                "game Ping Pong.\n "
                "Before we start do "
                "you wanna "
                "play with bot or with "
                "friend?\n If with bot "
                "enter 1, else 0\n";
        cin >> botOrNot;

        if (botOrNot == 1)
        {
            withBot = true;
        }
        else
        {
            withBot = false;
        }

        // Load media
        background = LoadBackground("Background.png", background);
        // Text texure
        FTexture scoreLeft("Mar.ttf", color, gRenderer, gFont);
        SDL_FRect rectLeftScore{0, 0, scoreLeft.getWidth(), scoreLeft.getHeight()};

        FTexture scoreRight("Mar.ttf", color, gRenderer, gFont);
        SDL_FRect rectRightScore{SCREEN_WIDTH - scoreLeft.getWidth(), 0, scoreLeft.getWidth(), scoreLeft.getHeight()};

        // Init Ball
        Ball ball(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.25, 0.25, 30, "Ball.png");
        ball.LoadMedia(gRenderer);
        SDL_FRect rectBall = ball.GetRect();
        // Inoti Players
        Player playerLeft(0, SCREEN_HEIGHT / 2 + 150 / 2, 0, 0, 20, "Player.png");
        playerLeft.LoadMedia(gRenderer);
        SDL_FRect rectPlayerLeft = playerLeft.GetRect();

        Player playerRight(SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2 + 150 / 2, 0, 0, 20, "Player.png");
        playerRight.LoadMedia(gRenderer);
        SDL_FRect rectPlayerRight = playerRight.GetRect();
        // Init bot
        Bot bot(SCREEN_WIDTH - 20, SCREEN_HEIGHT / 2 + 150 / 2, 0, 0, 20, "Player.png");
        bot.LoadMedia(gRenderer);
        SDL_FRect rectBot = bot.GetRect();

        SDL_Delay(2000);
        // Main loop flag
        bool quit = false;
        // Event handler
        SDL_Event e;

        // While application is running
        while (!quit)
        {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                // User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                // Player`s controls
                if (withBot)
                {
                    Player::Movement(e, playerLeft);
                }
                else
                {
                    Player::Movement(e, playerLeft, playerRight);
                }
            }

            if (ball.ballSkiped)
            {
                if (withBot)
                {
                    RestartGame(&ball, &playerLeft, &bot, &scoreLeft, &scoreRight);
                }
                else
                {
                    RestartGame(&ball, &playerLeft, &playerRight, &scoreLeft, &scoreRight);
                }
            }

            if (withBot)
            {
                ball.Update(rectBall, SCREEN_HEIGHT, SCREEN_WIDTH, playerLeft.GetRect(), bot.GetRect(), &gScoreLeft, &gScoreRight);
            }
            else
            {
                ball.Update(rectBall, SCREEN_HEIGHT, SCREEN_WIDTH, playerLeft.GetRect(), playerRight.GetRect(), &gScoreLeft, &gScoreRight);
            }

            playerLeft.Update(SCREEN_HEIGHT, rectPlayerLeft);

            if (withBot)
            {
                bot.Update(&ball, SCREEN_WIDTH, SCREEN_HEIGHT, rectBot);
            }
            else
            {
                playerRight.Update(SCREEN_HEIGHT, rectPlayerRight);
            }

            // Clear screen
            SDL_RenderClear(gRenderer);
            SDL_RenderCopyF(gRenderer, background, NULL, NULL);
            // Render texture to screen
            // scoreRight
            SDL_RenderCopyF(gRenderer, playerLeft.GetTexure(), NULL, &rectPlayerLeft);

            if (withBot)
            {
                SDL_RenderCopyF(gRenderer, bot.GetTexure(), NULL, &rectBot);
            }
            else
            {
                SDL_RenderCopyF(gRenderer, playerRight.GetTexure(), NULL, &rectPlayerRight);
            }

            SDL_RenderCopyF(gRenderer, scoreLeft.GetFontTexture(), NULL, &rectLeftScore);
            SDL_RenderCopyF(gRenderer, scoreRight.GetFontTexture(), NULL, &rectRightScore);

            SDL_RenderCopyF(gRenderer, ball.GetTexure(), NULL, &rectBall);
            // Update screen
            SDL_RenderPresent(gRenderer);
        }
    }

    // Free resources and close SDL
    close();
    return 0;
}

void RestartGame(Ball* ball, Player* paleyrLeft, Player* playerRight, FTexture* scoreLeft, FTexture* scoreRight)
{
    SDL_FRect pLeftRect{0, SCREEN_HEIGHT / 2, 0, 0};
    SDL_FRect pRightRect{SCREEN_WIDTH - playerRight->GetRect().w, SCREEN_HEIGHT / 2, 0, 0};

    scoreLeft->NewScore(&gScoreLeft, color, gRenderer, gFont);
    scoreRight->NewScore(&gScoreRight, color, gRenderer, gFont);

    SDL_Delay(2000);
    ball->SetPosition(startRect);
    ball->SetDx(-ball->GetDx());
    ball->SetDy(-ball->GetDy());

    playerRight->SetRect(pRightRect);
    paleyrLeft->SetRect(pLeftRect);

    ball->ballSkiped = false;
}
void RestartGame(Ball* ball, Player* paleyrLeft, Bot* bot, FTexture* scoreLeft, FTexture* scoreRight)
{
    SDL_FRect pLeftRect{0, SCREEN_HEIGHT / 2, 0, 0};
    SDL_FRect botRect{SCREEN_WIDTH - bot->GetRect().w, SCREEN_HEIGHT / 2, 0, 0};

    scoreLeft->NewScore(&gScoreLeft, color, gRenderer, gFont);
    scoreRight->NewScore(&gScoreRight, color, gRenderer, gFont);

    SDL_Delay(2000);
    ball->SetPosition(startRect);
    ball->SetDx(-ball->GetDx());
    ball->SetDy(-ball->GetDy());

    bot->SetRect(botRect);
    paleyrLeft->SetRect(pLeftRect);

    ball->ballSkiped = false;
}

bool init()
{
    // Initialization flag
    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! "
               "SDL Error: %s\n",
               SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to
        // linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear "
                   "texture filtering "
                   "not enabled!");
        }

        // Create window
        gWindow =
            SDL_CreateWindow("Ping Pong", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Window could not "
                   "be created! SDL "
                   "Error: %s\n",
                   SDL_GetError());
            success = false;
        }
        else
        {
            // Create renderer for
            // window
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
            if (gRenderer == NULL)
            {
                printf("Renderer could "
                       "not be created! "
                       "SDL Error: %s\n",
                       SDL_GetError());
                success = false;
            }
            else
            {
                // Initialize renderer
                // color
                SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

                // Initialize PNG
                // loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image "
                           "could not "
                           "initialize! "
                           "SDL_image "
                           "Error: %s\n",
                           IMG_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}
SDL_Texture* LoadBackground(string path, SDL_Texture* background)
{
    // Loading success flag
    bool success = true;

    SDL_Surface* newSurface = IMG_Load(path.c_str());

    if (newSurface == nullptr)
    {
        printf("Failed to load texture "
               "image!\n");
        success = false;
    }
    else
    {
        background = SDL_CreateTextureFromSurface(gRenderer, newSurface);
        if (background == nullptr)
        {
            std::cout << "Error text\n" << IMG_GetError();
        }

        SDL_FreeSurface(newSurface);
    }
    return background;
}
void close()
{
    // Free loaded image

    background = NULL;

    // Destroy window
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}