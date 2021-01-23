#ifndef _H_WRAPPER
#define _H_WRAPPER
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "utils.h"
#include "element.h"
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
        bool renderPart(SDL_Renderer **pr, int x, int y, int w, int h);

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


enum BUTTON_TYPE
{
    BUTTON_TYPE_MOUSE_OUT,
    BUTTON_TYPE_MOUSE_HANG,
    BUTTON_TYPE_MOUSE_DOWN,
    BUTTON_TYPE_MOUSE_UP
};

class ButtonWrapper
{
    public:
        ButtonWrapper(int button_w, int button_h);
        void setPosition(int x, int y);
        void handleEvent(SDL_Event *e);
        void renderBySprite(SDL_Renderer **pr, SpriteFactory *psprite, int row, int col, double angle);
        int getWidth();
        int getHeight();

    private:
        SDL_Point postion;
        BUTTON_TYPE current_type;
        int w;
        int h;

};


#endif