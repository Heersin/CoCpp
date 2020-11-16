#include "media.h"


int SDL_LIB_INIT_STATUS;
int SCREEN_WIDTH;
int SCREEN_HEIGHT;

// >>>>>>>>>>>>>>>>>>>>>>>>>>> Init And Close <<<<<<<<<<<<<<<<<
// Starts Up SDL
bool Init_SDL_lib()
{
    SDL_LIB_INIT_STATUS = SDL_LIB_UNINIT;

    // init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log_SDL_error();
        return false;
    }
    // set status
    SDL_LIB_INIT_STATUS |= SDL_LIB_MAIN_INIT;

    // init SDL IMAGE
    int img_flags = IMG_INIT_PNG;
    if( !(IMG_Init(img_flags) & img_flags) )
    {
        Log_SDL_IMG_error();
        return false;
    }
    // set status
    SDL_LIB_INIT_STATUS |= SDL_LIB_IMG_INIT;
    
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
	{
        printf( "Warning: Linear texture filtering not enabled!" );
        return false;
	}

    // init global to NULL
    SCREEN_WIDTH = 1280;
    SCREEN_HEIGHT = 720;
    return true;
}

// Free media and shut down SDL
void Close_SDL_lib()
{
    if ( (SDL_LIB_INIT_STATUS & SDL_LIB_IMG_INIT) == SDL_LIB_IMG_INIT )
        IMG_Quit();

    SDL_Quit();
}


// >>>>>>>>>>>>>>>>>>>>>>>>>> Basic Create Function <<<<<<<<<<<<<
// Create Window
bool Create_default_window(
    SDL_Window **pwindow,
    SDL_Surface **psurface,
    int width,
    int height,
    const char* title)
{
    *pwindow = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN);
    
    if(*pwindow == NULL)
    {
        Log_SDL_error();
        return false;
    }

    *psurface = SDL_GetWindowSurface(*pwindow);
    
    if(*psurface == NULL)
    {
        Log_SDL_error();
        return false;
    }

    return true;
}

// Create default render
bool Create_default_renderer_on_window(SDL_Renderer **prender, SDL_Window **pwindow)
{
    SDL_Window *window = *pwindow;
    *prender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if ( *prender == NULL )
    {
        printf("Render Not Init\n");
        Log_SDL_error();
        return false;
    }

    SDL_SetRenderDrawColor(*prender, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

// create texture
bool Create_texture(SDL_Renderer **prender, SDL_Texture **ptext, std::string path)
{
    if (prender == NULL || ptext == NULL)
        return false;

    SDL_Surface *load_surface = NULL;

    load_surface = Util_load_img(path);
    if (load_surface == NULL)
        return false;
    

    *ptext = SDL_CreateTextureFromSurface( *prender, load_surface );
    SDL_FreeSurface(load_surface);

    if (*ptext == NULL)
    { 
        Log_SDL_error();
        return false;
    } 
    
    return true;
}

// Functionality Functions
bool Set_viewport_on_render(SDL_Renderer **pr, int x, int y, int w, int h)
{
    SDL_Rect viewport;
    viewport.x = x;
    viewport.y = y;
    viewport.w = w;
    viewport.h = h;

    SDL_RenderSetViewport(*pr, &viewport);
}