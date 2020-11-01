#ifndef _H_WRAPPER
#define _H_WRAPPER
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "utils.h"
enum TTF_COLOR{
    TTF_COLOR_BLACK,
    TTF_COLOR_WHITE
};
class TextureWrapper
{
    public:
        // init 
        TextureWrapper();

        // de
        ~TextureWrapper();

        // load from a file
        bool loadFromFile(SDL_Renderer **pr, std::string path);
        bool loadFromText(SDL_Renderer **pr,TTF_Font **pfont, std::string text, TTF_COLOR color_type);

        // free our texture
        void freeTexture();

        // render somthing in (x,y) pos
        bool render(SDL_Renderer **pr, int x, int y);
        bool render(SDL_Renderer **pr, int x, int y, int w, int h);

        int getWidth();
        int getHeight();

        void setAlpha(Uint8 a);
    
    private:
        SDL_Texture* texture;

        // image dimension
        int width;
        int height;
        Uint8 alpha;
};



#endif