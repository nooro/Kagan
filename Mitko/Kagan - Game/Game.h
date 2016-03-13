#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <Entity.h>
#include "Background.h"
using namespace std;

class Game
{
private:
    int WINDOW_MAX_WIDTH;
    int WINDOW_MAX_HEIGHT;

    SDL_Renderer* renderer;
    SDL_Window* window;
    SDL_Event event;
    bool gameIsRunning = true;

    void LoadTheResources();
    void GameLoop();
    void CheckForEvents();
    void Render();
    void Exit();

    SDL_Background background;
    Entity character;

    struct bar
    {
        private:

            LGTexture texture;
            LGTexture textureFill;
            float x;
            float y;
            float scale;
            int window_x;
            int window_y;
            float currency = 100;


        public:

            void init(char* texture_file, SDL_Renderer* Rend, int screen_x, int screen_y, float x_, float y_, float scale_ = 1)
            {
                texture.load(Rend, texture_file, screen_x, screen_y);
                textureFill.load(Rend, "./resources/textures/fill.png", screen_x, screen_y);
                x = x_;
                y = y_;
                scale = scale_;
                window_x = screen_x;
                window_y = screen_y;
            }

            void render(SDL_Renderer* Rend)
            {
                float currency_percent = currency / 100;

                float fillX = x + 0.04 * texture.getWidth() / window_x;
                float fillY = y  + 0.08 * texture.getHeight() / window_y;
                float fillW = texture.getWidth() * 0.94;
                float fillH = texture.getHeight() * 0.35;

                fillW *= currency_percent;

                textureFill.set_dimensions(fillW, fillH);

                if(currency_percent < 0.5)
                    textureFill.setColorMod(255, currency_percent / 0.5 * 255, 0);
                if(currency_percent >= 0.5)
                    textureFill.setColorMod((1 - currency_percent) / 0.5 * 255, 255, 0);

                textureFill.render(Rend, fillX, fillY, scale);
                texture.render(Rend, x, y, scale);
            }

            void setCurrency(float currency_)
            {
                currency = currency_;
            }

    }health_bar, stamina_bar;

public:
    Game();
    void Run(string username);

};

#endif // GAME_H
