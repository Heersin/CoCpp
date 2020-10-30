#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Starts Up SDL
bool Init_SDL_lib();
void Close_SDL_lib();
void Log_SDL_error();
void Log_SDL_IMG_error();


bool Create_default_window(
    SDL_Window *window,
    SDL_Surface *surface,
    int width,
    int height,
    const char* title);
bool Create_texture(SDL_Renderer **pr, SDL_Texture **ptext, std::string path);
bool Create_default_renderer_on_window(SDL_Renderer **pr, SDL_Window **pw);


SDL_Surface *Util_load_bmp(std::string path);
SDL_Surface *Util_load_img(std::string path);

// global var
int SDL_LIB_INIT_STATUS;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;

#define SDL_LIB_MAIN_INIT 1
#define SDL_LIB_IMG_INIT 2
#define SDL_LIB_UNINIT 0