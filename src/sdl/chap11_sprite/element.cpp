#include "element.h"

SpriteFactory::SpriteFactory()
{
    clips = NULL;
    texture = NULL;
    width = 0;
    height = 0;
    clip_w = 0;
    clip_h = 0;
    clips_col = 0;
    clips_row = 0;
    cnt = 0;
    alpha = 255;
}

SpriteFactory::~SpriteFactory()
{
    freeSprite();
}

bool SpriteFactory::procSprite(SDL_Renderer **pr, std::string path, int n_row, int n_col)
{
    // clear previous spirite
    this->freeSprite();

    SDL_Texture *cur_texture = NULL;
    SDL_Surface *img = Util_load_img(path);
    if (img == NULL)
    {
        Log_SDL_IMG_error();
        return false;
    }

    // create texture on outside given render
    cur_texture = SDL_CreateTextureFromSurface(*pr, img);

    if (cur_texture == NULL)
    {
        // give up
        Log_SDL_error();
        SDL_FreeSurface(img);
        return false;
    }

    // calculate clip policy
    int per_w, per_h, cur_cnt;
    per_w = img->w / n_col;
    per_h = img->h / n_row;
    cur_cnt = n_col * n_row;

    // alloc pointers
    clips = (SDL_Rect **)malloc(sizeof(SDL_Rect *) * cur_cnt);
    // TODO error handle

    // SDL rect
    SDL_Rect *render_quad = NULL;
    
    for(int i = 0; i < n_row; ++i)
    {
        for (int j = 0; j < n_col; ++j )
        {
            render_quad = new SDL_Rect;
            render_quad->x = j * per_w;
            render_quad->y = i * per_h;
            render_quad->w = per_w;
            render_quad->h = per_h;
            clips[i * n_col + j] = render_quad;
        }

    }

    // update class
    width = img->w;
    height = img->h;
    texture = cur_texture;
    clip_w = per_w;
    clip_h = per_h;
    cnt = cur_cnt;
    clips_col = n_col;
    clips_row = n_row;

    // free surface
    SDL_FreeSurface(img);
    return true;
}

void SpriteFactory::freeSprite()
{
    if(clips != NULL)
    {
        for(int i; i < cnt; ++i)
            delete clips[i];
        
        free(clips);
    }
    clips = NULL;

    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
        clip_h = 0;
        clip_w = 0;
        clips_row = 0;
        clips_col = 0;
        cnt = 0;
        alpha = 255;
    }
}


SDL_Rect* SpriteFactory::getClip(int row, int col)
{
    return clips[row * clips_col + col];
}

bool SpriteFactory::renderClip(SDL_Renderer **pr, int x, int y, int row, int col)
{
    SDL_Rect render_quad = {x, y, 0, 0};

    render_quad.w = clip_w;
    render_quad.h = clip_h;

    int result = SDL_RenderCopy(*pr, texture, clips[row * clips_col + col], &render_quad);
    if (result == 0)
        return true;
    return false;
}

int SpriteFactory::getWidth()
{
    return width;
}
int  SpriteFactory::getHeight()
{
    return height;
}
int  SpriteFactory::getClipWidth()
{
    return clip_w;
}
int  SpriteFactory::getClipHeight()
{
    return clip_h;
}
int  SpriteFactory::getTotalNum()
{
    return cnt;
}
void SpriteFactory::setAlpha(Uint8 a)
{
    alpha = a;
    SDL_SetTextureAlphaMod( texture, alpha );
}