#ifndef HOME_H_INCLUDED
#define HOME_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "../General/General.h"
#include "../GUI/Button.h"
using namespace std;

class Home
{
public:
    Home();
    ~Home();

private:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

    SDL_Texture *backgroundTexture = NULL;
    bool homeWindowIsActive;

    void MainLoop();
    void CheckForEvents();
    void InitTheTextures();

    TTF_Font *font_chiller;

    //User-name label
    void InitTheUsernameLabel();
    SDL_Texture *usernameLabel = NULL;
    SDL_Rect usernameLabelRect;
    SDL_Color usernameLabelColor;
    string usernameLabelText;

    //Character bar
    void InitTheCharacterBar();
    SDL_Texture *characterBarBackground = NULL;
    SDL_Rect characterBarRect;

    //Character animation
    SDL_Texture *characterTexture = NULL;
    SDL_Rect characterRect;
    SDL_Rect spriteSheetRect;
    void AnimateTheCharacter();

    //Play button
    Button playButton;
    SDL_Texture *playButtonTexture = NULL;
    SDL_Texture *playButtonHoverTexture = NULL;
    void InitThePlayButton();

    //Cursor
    SDL_Texture *cursor = NULL;
    SDL_Rect cursorRect;
};

#endif // HOME_H_INCLUDED
