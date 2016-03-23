#ifndef LOGIN_H_INCLUDED
#define LOGIN_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <windows.h>

#include "ServerCommunication.h"
#include "../GUI/Button.h"
#include "../GUI/InputField.h"
using namespace std;

class Register
{
public:
    Register(); //Initialize everything for the registration. Create register window with fields to enter user-name and password. Send the data to the server.
    ~Register(); //Free the used memory.
    char Status(); //Return if the register is successful or not.

private:
    char *serverIP = "127.0.0.1";
    SDL_Texture *inputFieldTexture = NULL;
    SDL_Texture *inputFieldTextureHover = NULL;
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Event event;

    SDL_Texture *windowBorder = NULL;
    SDL_Texture *logoTexture = NULL;
    SDL_Rect logoRect;
    SDL_Texture *backgroundTexture = NULL;

    TTF_Font *labelFont;
    SDL_Texture *usernameLabel;
    SDL_Texture *passwordLabel;
    SDL_Texture *passwordRepeatLabel;

    SDL_Rect usernameLabelRect;
    SDL_Rect passwordLabelRect;
    SDL_Rect passwordRepeatLabelRect;
    SDL_Color labelColor;

    InputField *usernameInputField;
    InputField *passwordInputField;
    InputField *passwordRepeatInputField;

    Button registerButton;
    SDL_Texture *buttonTexture = NULL;
    SDL_Texture *buttonHoverTexture = NULL;
    SDL_Texture *buttonText = NULL;

    bool registerWindowIsActive;
    void Loop();
    void InitTheButton();
    void InitTheInputFields();
    void InitTheTextures();
};

#endif // LOGIN_H_INCLUDED
