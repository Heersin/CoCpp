# README

As A milestone, chap20 provides the basic support about Texture, Button Element, Sprite, animation, text rendering, audio and keyhandler.
So It would be better to write a simple document about this project which displays the structure of it and API.

## Overview
to be honest, it's a "flat" project now. that means all header file and cpp file have been placed under the same path.
```
sdl/chap20_time
├── audio.cpp 
├── audio.h --- audio support
├── element.cpp 
├── element.h --- design for "static" resource, like sprite factory
├── key_event.cpp
├── key_event.h --- handle key event
├── main.cpp --- main function
├── Makefile
├── media --- binary
├── media.cpp --- functions used in main.cpp
├── media.h --- main's header
├── README.md
├── rsrc --- resources for this program
│   ├── 0.wav
│   ├── 1.wav
│   ├── 2.wav
│   ├── ani.png
│   ├── button.png
│   ├── kizuna.png
│   ├── lazy.ttf
│   ├── music.wav
│   ├── night.png
│   └── uni.png
├── timer.cpp
├── timer.h --- timer
├── utils.cpp 
├── utils.h --- util functions
├── wrapper.cpp
└── wrapper.h --- wrapper of Texture
```

## API

### Window and render
* <media.h>
Until now, this program has one window and one render in main. it might be more in the future, but I don't care.
so I create them as C-like function instead of Cpp-like class.

#### Init_SDL_lib() & Close_SDL_lib()
a pair of functions for lib init and lib close, call them in the very first and the very last respectively
```C++
Init_SDL_lib()
...
CLose_SDL_lib()
return 0;
```
#### Create_default_window()
```C++
Create_default_window(
    SDL_Window **pwindow,
    SDL_Surface **psurface,
    int width,
    int height,
    const char* title);
```
the pwindow and psurface are two variable to recive the result (aka pointer of an empty variable)


Example:
```C++
SDL_Window *base_window = NULL;
SDL_Surface *base_surface = NULL;
Create_default_window(
    &base_window,
    &base_surface,
    a,
    b,
    "xx"
)
```

#### Create_default_renderer_on_window
Create_default_renderer_on_window(SDL_Renderer **pr, SDL_Window **pw);
* pr is the recive pointer
* but pw is an pointer points to exsiting SDL_Window *.

#### Create_ttf_font
Create_ttf_font(TTF_Font **pfont, std::string path, int ptsize);
* pfont is a recive pointer

#### Mini Map
bool Set_viewport_on_render(SDL_Renderer **pr, int x, int y, int w, int h);

### wrapper
* <wrapper.h>
only Texture wrapper now, the texture wrapper wrapped basic usage of Texture and add error report to it as a Texture Class.
There r 2 types of Texture at the moment:

#### General Texture Wrapper
```c++
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
```

it has 4 attributes:
1. texture is the inner texture, it's totally private.
2. width, height as u know.
3. alpha -- control the opacity of Texture.

Example of using a Texture:
```C++
TextureWrapper texture_A;
texture_A.loadFromeFile(&base_render, path_to_load_img);
...
texture_A.render(&base_render, x, y);
...
texture_A.freeTexture();
```
the diffrence between two "render" methods is args. the second one (accept 5 args) controls the position(x,y) and its shape(width, height)

to render a text, use `loadFromText`, font can be NULL:
```C++
texture_A.loadFromText(&base_render, &font, "Here is A", TTF_COLOR_BLACK);
```

the color type is an Enum:
```C++
enum TTF_COLOR{
    TTF_COLOR_BLACK,
    TTF_COLOR_WHITE
};
```

Note that u can reload image or text since the `load*` family have builtin detect-and-free technique.

#### Button Wrapper
```C++
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
```

A more specified Texture Wrapper for Button Creation
requires SpriteFactory to load image.

```C++
SpriteFactory sprite_UI_elements;
...

ButtonWrapper button = (WIDTH, HEIGHT);
button.setPosition(x, y); // set position of button
button.renderBySprite(&base_render, &sprite_UI_elements, 3, 5, 0); // render the 4th row, 6th col element in sprite, no rotation
...

// in event poll loop
    button.handleEvent(&e);
```

should overwrite the handleEvent to fullfill your needs.

### Element
* <element.h>

```C++
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
```

Sprite is a static resource which reside in memory. this factory will load and clip Sprite to element arrays according to the given row and col.
index start from 0. so you can keep an factory which loads a Sprite containing required UI images. Render part of it to target texture.

Example:
```C++
SpriteFactory UI;
UI.procSprite(&base_render, path_to_it, 5, 5); // support it's a 5 * 5 Sprite
...

// render it to Texture, button .etc
```

### Audio
```C++
class MusicPlayer
{
    public:
        // player create and destroy
        MusicPlayer(int max_music, int max_chunk);
        void freePlayer();
        void loadMusic(std::string path);
        void loadMusicChunk(std::string path);

        // player action
        void playChunk(int id);
        void playMusic(int id);
        void pauseMusic();
        void stopMusic();
        void resumeMusic();

        // player status check
        bool isPlaying();
        bool isPaused();

        // playere atrribute
        int getCurrentMusicNum();
        int getCurrentChunkNum();

    private:
        Mix_Music **musics;
        Mix_Chunk **chunks;
        int max_music_num;
        int max_chunk_num;
        // record current hold chunk/music number
        int cur_music_id;
        int cur_chunk_id;
};
```
load and play music. create it with (music_num, chunk_num)


### Timer
like a stop watch.

### Key Event
two type of key Handler support.
one handle with SDL_event, one with inner array of SDL lib.

### Utils
most of them are error report
SDL_Surface *Util_load_img(std::string path);
SDL_Surface *Util_load_bmp(std::string path);

void Log_SDL_error();
void Log_SDL_IMG_error();
void Log_SDL_TTF_error();
void Log_SDL_MIXER_error();