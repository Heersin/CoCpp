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
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
    
    // init SDL ttf
    if( TTF_Init() == -1 )
    {
        Log_SDL_TTF_error();
        return false;
    }
    // set status
    SDL_LIB_INIT_STATUS |= SDL_LIB_TTF_INIT;

    // init Mixer
    if( Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        Log_SDL_MIXER_error();
        return false;
    }
    SDL_LIB_INIT_STATUS |= SDL_LIB_MIXER_INIT;

    // set hint
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
    if ( (SDL_LIB_INIT_STATUS & SDL_LIB_TTF_INIT) == SDL_LIB_TTF_INIT)
        TTF_Quit();
    if ( (SDL_LIB_INIT_STATUS & SDL_LIB_MIXER_INIT) == SDL_LIB_MIXER_INIT )
        Mix_Quit();

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

    //*prender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    *prender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if ( *prender == NULL )
    {
        printf("Render Not Init\n");
        Log_SDL_error();
        return false;
    }

    SDL_SetRenderDrawColor(*prender, 0xFF, 0xFF, 0xFF, 0xFF);
    return true;
}

bool Create_ttf_font(TTF_Font **pfont, std::string path, int ptsize)
{
    *pfont = TTF_OpenFont(path.c_str(), ptsize);
    if ( *pfont == NULL )
    {
        Log_SDL_TTF_error();
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