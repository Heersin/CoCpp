#include "utils.h"
// >>>>>>>>>>>>>>>>>>> Support Format Process <<<<<<<<<<<<<<
// Loads bmp 
SDL_Surface *Util_load_bmp(std::string path)
{
    SDL_Surface *new_surface = NULL;
    new_surface = SDL_LoadBMP(path.c_str());
    if(new_surface == NULL){
        printf("Load BMP Failed\n");
        Log_SDL_error();
        return NULL;
    }
    return new_surface;
}


// Loads img 
SDL_Surface *Util_load_img(std::string path)
{
    SDL_Surface *new_surface = NULL;
    new_surface = IMG_Load(path.c_str());
    if(new_surface == NULL){
        printf("Load IMG Failed\n");
        Log_SDL_IMG_error();
        return NULL;
    }
    return new_surface;
}


void Log_SDL_error()
{
    printf("SDL Error : %s \n", SDL_GetError());
}

void Log_SDL_IMG_error()
{
    printf("SDL IMAGE Error : %s \n", IMG_GetError());
}
