#ifndef _MEDIA_H
#define _MEDIA_H
/**********
* Main program's header
* some init and default creator 
**********/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string.h>
#include <sstream>
#include "base_com/utils.h"
#include "base_com/wrapper.h"
#include "base_com/element.h"
#include "base_com/audio.h"
#include "base_com/timer.h"
#include "components/role.h"
#include "components/focusBackground.h"

// MACRO
#define SDL_LIB_MAIN_INIT 1
#define SDL_LIB_IMG_INIT 2
#define SDL_LIB_TTF_INIT 4
#define SDL_LIB_MIXER_INIT 8
#define SDL_LIB_UNINIT 0

// Starts Up SDL
bool Init_SDL_lib();
void Close_SDL_lib();


bool Create_default_window(
    SDL_Window **pwindow,
    SDL_Surface **psurface,
    int width,
    int height,
    const char* title);
bool Create_default_renderer_on_window(SDL_Renderer **pr, SDL_Window **pw);
bool Create_ttf_font(TTF_Font **pfont, std::string path, int ptsize);

// functionality
bool Set_viewport_on_render(SDL_Renderer **pr, int x, int y, int w, int h);

// global var on main
extern int SDL_LIB_INIT_STATUS;
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#endif