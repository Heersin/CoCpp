#include "media.h"

Timer global_timer;
// >>>>>>>>>>>>>> Main Part <<<<<<<<<<<<<<<<<
int main()
{
    // surface on window
    // SDL_Window *base_window;
    // SDL_Surface *base_surface;

    // render on window
    SDL_Renderer *base_render;
    TTF_Font *base_font;

    base_render = NULL;
    base_font = NULL;

    WindowWrapper base_window;

    // init 
    if(!Init_SDL_lib())
    {
        printf("Failed to init SDL\n");
        return -1;
    }

    // create our window
    if(!base_window.init())
    {
        printf("Failed to create default window\n");
        Close_SDL_lib();
        return -1;
    }

    // create renderer on window
    if((base_render = base_window.createRenderer()) == NULL)
    {
        printf("Failed to create renderer on window\n");
        base_window.free();
        Close_SDL_lib();
        return -1;
    }

    // create font
    if( !Create_ttf_font(&base_font, "rsrc/alex-Italic.ttf", 28) )
    {
        printf("Failed to load ttf font file\n");
        base_window.free();
        Close_SDL_lib();
        return -1;
    }

// >>>>>>>>>>>>>>>> Main Event Loop <<<<<<<<<<<<<<<<<<<<<<,
    bool quit = false;
    SDL_Event e;
    MusicPlayer unique_player(1,3);

    // test music
    unique_player.loadMusic("rsrc/music.wav");
    unique_player.loadMusicChunk("rsrc/0.wav");
    unique_player.loadMusicChunk("rsrc/1.wav");
    unique_player.loadMusicChunk("rsrc/2.wav");

    // play music 0
    unique_player.playMusic(0);

    // Clear Screen
    SDL_SetRenderDrawColor(base_render, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(base_render);

    // Texture Wrapper
    TextureWrapper text_line;
    TextureWrapper text_title;

    text_title.loadFromText(&base_render, &base_font, "Text Board", TTF_COLOR_BLACK);
    
    
    // add an text
    std::string textboard_string = "Input Here...";
    text_line.loadFromText(&base_render, &base_font, textboard_string.c_str(), TTF_COLOR_BLACK); 

    
    // start text input
    SDL_StartTextInput();


    while(!quit)
    {
        bool render_text_flag = false;
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;

            else if (e.type == SDL_KEYDOWN)
            {
                // BackSpace Delete
                if (e.key.keysym.sym == SDLK_BACKSPACE && textboard_string.length() > 0)
                {
                    textboard_string.pop_back();
                    render_text_flag = true;
                }

                // copy clipboard ctrl+C
                else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
                {
                    SDL_SetClipboardText(textboard_string.c_str());
                }

                // paste ctrl+V
                else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
                {
                    textboard_string = SDL_GetClipboardText();
                    render_text_flag = true;
                }

                // save to file ctrl+S
                else if (e.key.keysym.sym == SDLK_s && SDL_GetModState() & KMOD_CTRL)
                {
                    SDL_RWops *file = SDL_RWFromFile("last.log", "w+");
                    if (file == NULL)
                    {
                        printf("Unable to open as write : %s\n", SDL_GetError());
                        continue;
                    }
                    SDL_RWwrite(
                        file, 
                        textboard_string.c_str(), 
                        sizeof(char), 
                        textboard_string.length());
                    SDL_RWclose(file);
                }

                else if (e.key.keysym.sym == SDLK_RETURN)
                {
                    textboard_string += "\n";
                    render_text_flag = true;
                    printf("Enter pressed\n");
                }
            }


            // handle input
            else if (e.type == SDL_TEXTINPUT)
            {
                // exclude the ctrl+c and ctrl+v
                if(!(SDL_GetModState() & KMOD_CTRL && 
                        (e.text.text[0] == 'c' || 
                        e.text.text[0] == 'C' || 
                        e.text.text[0] == 'v' || 
                        e.text.text[0] == 'V' )))
                {
                    textboard_string += e.text.text;
                    render_text_flag = true;
                }
            }

            else
            {
                base_window.handleEvent(e);
            }
        }

        // after poll , the key state will be refresh


        if (render_text_flag)
        {
            if (textboard_string != "")
                text_line.loadFromText(&base_render, &base_font, textboard_string.c_str(), TTF_COLOR_BLACK);
            
            //render empty text
            else
                text_line.loadFromText(&base_render, &base_font, " ", TTF_COLOR_BLACK);
        }

        // Clear Screen
        SDL_SetRenderDrawColor(base_render, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(base_render);

        
        // render text title
        text_title.render(
            &base_render,
            SCREEN_WIDTH / 3,
            SCREEN_HEIGHT / 10
        );

        // render text board
        text_line.render(
            &base_render,
            0,
            SCREEN_HEIGHT / 5
        );
        
        // update screen
        SDL_RenderPresent(base_render);
    }

    SDL_StopTextInput();
    // close and clean
    // clean
    text_line.freeTexture();
    text_title.freeTexture();
    base_window.free();

    // close
    Close_SDL_lib();
    return 0;
}