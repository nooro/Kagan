#include "InputField.h"

InputField::InputField(SDL_Renderer *renderer)
{
    render = renderer;
    if(render == NULL)
        cout << "Failed to create the input field renderer: " << endl;

    type = "normal";

    isActive = false;
    if(TTF_Init() < 0)
        cout << "Failed to initialize TTF: " << TTF_GetError() << endl;

    font = TTF_OpenFont("Resources/Fonts/Chiller.ttf", 999);

    if(font == NULL)
        cout << "Failed to open the font: " << TTF_GetError() << endl;

    rect = {0, 0, 0, 0};
    SDL_RenderPresent(render);
    textColor = {255, 255, 255, 0};
}

InputField::~InputField()
{
    TTF_CloseFont(font);
    TTF_Quit();
}

void InputField::Render()
{
    SDL_RenderCopy(render, texture, NULL, &rect);
    SDL_RenderCopy(render, inputTexture, NULL, &rect);

}

void InputField::RenderHover()
{
    SDL_RenderCopy(render, hoverTexture, NULL, &rect);
    SDL_RenderCopy(render, inputTexture, NULL, &rect);
    SDL_RenderPresent(render);
}


void InputField::Input(SDL_Event *e)
{
    if(e->type == SDL_KEYDOWN  && isActive)
    {
        if(e->key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
        {
            inputText.pop_back();
            inputTexture = CreateTextTexture(render, inputText, font, rect.w - charLimit, textColor);
        }
        else if(e->key.keysym.sym == SDLK_RETURN || e->key.keysym.sym == SDLK_RETURN2)
            isActive = false;
        else if(e->key.keysym.sym == SDLK_TAB)
            isActive = false;
        else
        {
            if(inputText.length() < charLimit)
            {
                inputText += (char)e->key.keysym.sym;

                if(type == "normal")
                    inputTexture = CreateTextTexture(render, inputText, font, rect.w / charLimit, textColor);
                else if(type == "password")
                {
                    string passToShow;
                    for(int i = 0; i < inputText.length(); ++i)
                        passToShow += '*';
                    inputTexture = CreateTextTexture(render, passToShow, font, rect.w / charLimit, textColor);
                }
            }
        }
    }
}

string InputField::GetInputText() { return inputText; }

void InputField::SetCharLimit(int limit) { charLimit = limit; }

void InputField::SetTextColor(int r, int g, int b, int a) { textColor = {r, g, b, a}; }
