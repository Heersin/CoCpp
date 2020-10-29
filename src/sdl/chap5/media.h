#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>

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

SDL_Surface *Load_surface(std::string path);

// global var
enum KEY_PRESS_SURFACES
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};
SDL_Surface *g_current_surface;
SDL_Surface *g_keypress_surface_array[KEY_PRESS_SURFACE_TOTAL];
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
