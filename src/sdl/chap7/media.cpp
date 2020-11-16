#include "media.h"

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
    SCREEN_WIDTH = 640;
    SCREEN_HEIGHT = 480;
    return true;
}

// Free media and shut down SDL
void Close_SDL_lib()
{
    if ( (SDL_LIB_INIT_STATUS & SDL_LIB_IMG_INIT) == SDL_LIB_IMG_INIT )
        IMG_Quit();

    SDL_Quit();
}

void Log_SDL_error()
{
    printf("SDL Error : %s \n", SDL_GetError());
}

void Log_SDL_IMG_error()
{
    printf("SDL IMAGE Error : %s \n", IMG_GetError());
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

// >>>>>>>>>>>>>>>>>>> Support Format Process <<<<<<<<<<<<<<
// Loads bmp 
SDL_Surface *Util_load_bmp(std::string path)
{
    SDL_Surface *new_surface = NULL;
    new_surface = SDL_LoadBMP(path.c_str());
    if(new_surface == NULL){
        printf("Load BMP Failed\n");
        Log_SDL_error();
        return NULL;
    }
    return new_surface;
}


// Loads img 
SDL_Surface *Util_load_img(std::string path)
{
    SDL_Surface *new_surface = NULL;
    new_surface = IMG_Load(path.c_str());
    if(new_surface == NULL){
        printf("Load IMG Failed\n");
        Log_SDL_IMG_error();
        return NULL;
    }
    return new_surface;
}


// >>>>>>>>>>>>>> Main Part <<<<<<<<<<<<<<<<<
int main()
{
    // surface on window
    SDL_Window *base_window;
    SDL_Surface *base_surface;

    // texture on render
    SDL_Renderer *base_render;
    SDL_Texture *base_texture;

    base_window = NULL;
    base_surface = NULL;
    base_render = NULL;
    base_texture = NULL;
    // init 
    if(!Init_SDL_lib())
    {
        printf("Failed to init SDL\n");
        return -1;
    }

    // create our window
    if(!Create_default_window(
                &base_window,
                &base_surface,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                "SDL Example"))
    {
        printf("Failed to create default window\n");
        Close_SDL_lib();
        return -1;
    }

    // create renderer on window
    if(!Create_default_renderer_on_window(&base_render, &base_window))
    {
        printf("Failed to create renderer on window\n");
        SDL_DestroyWindow( base_window );
        Close_SDL_lib();
        return -1;
    }

    // create Texture on renderer
    if(!Create_texture( &base_render, &base_texture, "rsrc/default.png"))
    {
        printf("Failed to create render\n");
        SDL_DestroyRenderer( base_render );
        SDL_DestroyWindow( base_window );
        Close_SDL_lib();
        return -1;
    }

    // Perform Bad on KDE (x11 based)
    // which showed an empty window
    // SDL_Delay(2000);

    bool quit = false;
    SDL_Event e;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
            if (e.type == SDL_QUIT)
                quit = true;
        
        // Clear screen
        SDL_RenderClear(base_render);
        // render textuer
        SDL_RenderCopy(base_render, base_texture, NULL, NULL);
        //update screen
        SDL_RenderPresent(base_render);
    }

    // close and clean
    SDL_DestroyTexture( base_texture );
    SDL_DestroyRenderer( base_render );
    SDL_DestroyWindow( base_window );
    Close_SDL_lib();
    return 0;
}