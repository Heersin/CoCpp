#include "wrapper.h"
TextureWrapper::TextureWrapper()
{
    texture = NULL;
    width = 0;
    height = 0;
    alpha = 255;
}

TextureWrapper::~TextureWrapper()
{
    freeTexture();
}

bool TextureWrapper::loadFromFile(SDL_Renderer **pr, std::string path)
{
    // clear previous texture
    this->freeTexture();

    SDL_Texture *new_texture = NULL;
    SDL_Surface *img = Util_load_img(path);
    if (img == NULL)
    {
        Log_SDL_IMG_error();
        return false;
    }

    // color key on img
    // arg0 - surface to color key
    // arg1 - enable
    // arg3 - color panel
    // SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 0, 0xFF, 0xFF));

    // create texture on outside given render
    new_texture = SDL_CreateTextureFromSurface(*pr, img);

    if (new_texture == NULL)
    {
        Log_SDL_error();
        SDL_FreeSurface(img);
        return false;
    }

    width = img->w;
    height = img->h;
    texture = new_texture;

    // free surface
    SDL_FreeSurface(img);
    return true;
}

// file
bool TextureWrapper::loadFromText(SDL_Renderer **pr,TTF_Font **pfont, std::string text, TTF_COLOR color_type)
{
    // clear previous texture
    this->freeTexture();

    SDL_Texture *new_texture = NULL;
    SDL_Color text_color;
    
    switch(color_type)
    {
        case TTF_COLOR_BLACK:
            text_color = {0, 0, 0};
            break;
        default:
            text_color = {0, 0, 0};
            break;
    }

    SDL_Surface *text_surface = TTF_RenderText_Solid( *pfont, text.c_str(), text_color );

    if (text_surface == NULL)
    {
        Log_SDL_TTF_error();
        return false;
    }

    // create texture on outside given render
    new_texture = SDL_CreateTextureFromSurface(*pr, text_surface);

    if (new_texture == NULL)
    {
        Log_SDL_error();
        SDL_FreeSurface(text_surface);
        return false;
    }

    width = text_surface->w;
    height = text_surface->h;
    texture = new_texture;

    // free surface
    SDL_FreeSurface(text_surface);
    return true;
}

void TextureWrapper::freeTexture()
{
    if(texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture = NULL;
        width = 0;
        height = 0;
        alpha = 255;
    }
}

bool TextureWrapper::render(SDL_Renderer **pr, int x, int y)
{
    SDL_Rect renderQuad = {x, y, width, height};
    int result = SDL_RenderCopy( *pr, texture, NULL, &renderQuad );
    if (result == 0)
        return true;
    return false;
}

// override
bool TextureWrapper::render(SDL_Renderer **pr, int x, int y, int w, int h)
{
    SDL_Rect renderQuad = {x, y, w, h};
    int result = SDL_RenderCopy( *pr, texture, NULL, &renderQuad );
    if (result == 0)
        return true;
    return false;
}

int TextureWrapper::getWidth()
{
    return width;
}

int TextureWrapper::getHeight()
{
    return height;
}

void TextureWrapper::setAlpha(Uint8 a)
{
    alpha = a;
    SDL_SetTextureAlphaMod( texture, alpha );
}

// >>>>>>>>>>>>>>>>>>>>>>>>>> Button Class <<<<<<<<<<<<<<<<<<<<<<<
ButtonWrapper::ButtonWrapper(int button_w, int button_h)
{
    postion.x = 0;
    postion.y = 0;
    w = button_w;
    h = button_h;
    current_type = BUTTON_TYPE_MOUSE_OUT;
}

void ButtonWrapper::setPosition(int x, int y)
{
    postion.x = x;
    postion.y = y;
}

void ButtonWrapper::handleEvent(SDL_Event *e)
{
    // if mouse event happend
    if(e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
    {
        // get mouse postion
        int x, y;
        SDL_GetMouseState( &x, &y );

        // check if mouse in button
        bool inside = true;

        // mouse is left of button
        if( (x < postion.x) || \
            (x > postion.x + w) || \
            (y < postion.y) || \
            (y > postion.y + h))
            inside = false;
        
        if(!inside)
            current_type = BUTTON_TYPE_MOUSE_OUT;
        // else mouse is inside
        else
            switch(e->type)
            {
                case SDL_MOUSEMOTION:
                    current_type = BUTTON_TYPE_MOUSE_HANG;
                    printf("Button Hang\n");
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    current_type = BUTTON_TYPE_MOUSE_DOWN;
                    printf("Button Down\n");
                    break;
                case SDL_MOUSEBUTTONUP:
                    current_type = BUTTON_TYPE_MOUSE_UP;
                    printf("Button UP\n");
                    break;
                default:
                    printf("Button Default\n");
                    current_type = BUTTON_TYPE_MOUSE_HANG;
                    break;
            }
    }
}


void ButtonWrapper::renderBySprite(SDL_Renderer **pr, SpriteFactory *psprite, int row, int col, double angle)
{
    psprite->renderClip(pr, postion.x, postion.y, row, col, angle);
}

int ButtonWrapper::getWidth()
{
    return w;
}

int ButtonWrapper::getHeight()
{
    return h;
}




