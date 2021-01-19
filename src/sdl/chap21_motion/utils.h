#ifndef _UTILS_H
#define _UTILS_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
// utils to help me handle diffrent formats and others
SDL_Surface *Util_load_img(std::string path);
SDL_Surface *Util_load_bmp(std::string path);

void Log_SDL_error();
void Log_SDL_IMG_error();
void Log_SDL_TTF_error();
void Log_SDL_MIXER_error();
#endif