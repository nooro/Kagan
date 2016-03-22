#include "Game.h"

void Game::Cleanup()
{

    ///Free memory

    //Mixer

    SDL_FreeCursor(Cursor);
    SDL_FreeCursor(DragCursor);

    //SDL

    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_DestroyTexture(empty_layer.Tileset_Image);
    SDL_DestroyTexture(empty_layer.Hover_Image);
    SDL_FreeSurface(Icon);
    SDL_Quit();
}
