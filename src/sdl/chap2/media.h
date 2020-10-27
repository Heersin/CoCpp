#include <SDL2/SDL.h>
#include <stdio.h>

// Starts Up SDL
bool Init_SDL_lib();

// Create Window
bool Create_default_window(
    SDL_Window *window,
    SDL_Surface *surface,
    int width,
    int height,
    const char* title);

// Loads media
bool Load_media();

// Free media and shut down SDL
void Close_SDL_lib();

void Log_SDL_error();

// global var
SDL_Surface *gHelloWorld;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;