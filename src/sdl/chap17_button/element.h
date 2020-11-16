#ifndef _H_ELEMENT
#define _H_ELEMENT

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils.h"

// >>>>>>>>>>> Sprite <<<<<<<<<<<<<
class SpriteFactory
{
    public:
        SpriteFactory();
        ~SpriteFactory();

        // load sprite and proc
        // row and col as args
        bool procSprite(
            SDL_Renderer **pr,
            std::string path,
            int n_row,
            int n_col);

        // free sprite
        void freeSprite();

        // load sprite clip
        SDL_Rect *getClip(int row, int col);
        // render clip
        bool renderClip(SDL_Renderer **pr, int x, int y, int row, int col);
        bool renderClip(SDL_Renderer **pr, int x, int y, int row, int col, double angle);

        // getter
        int getWidth();
        int getHeight();
        int getClipWidth();
        int getClipHeight();
        int getTotalNum();

        void setAlpha(Uint8 a);

    private:
        SDL_Rect **clips;
        SDL_Texture *texture;

        int width;
        int height;
        int clip_w;
        int clip_h;
        int cnt;
        int clips_row;
        int clips_col;
        int alpha;
};

#endif