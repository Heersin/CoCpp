#ifndef _H_WRAPPER
#define _H_WRAPPER
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils.h"
class TextureWrapper
{
    public:
        // init 
        TextureWrapper();

        // de
        ~TextureWrapper();

        // load from a file
        bool loadFromFile(SDL_Renderer **pr, std::string path);

        // free our texture
        void freeTexture();

        // render somthing in (x,y) pos
        bool render(SDL_Renderer **pr, int x, int y);
        bool render(SDL_Renderer **pr, int x, int y, int w, int h);

        int getWidth();
        int getHeight();
    
    private:
        SDL_Texture* texture;

        // image dimension
        int width;
        int height;
};


#endif