#ifndef CREATETEXTURE_H_INCLUDED
#define CREATETEXTURE_H_INCLUDED

SDL_Texture *CreateTexture(std::string filePath, SDL_Renderer* textureRenderer){
    SDL_Texture* texture = NULL;
    SDL_Surface* temp_surface = IMG_Load(filePath.c_str());

    texture = SDL_CreateTextureFromSurface(textureRenderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    return texture;
}

#endif // CREATETEXTURE_H_INCLUDED
