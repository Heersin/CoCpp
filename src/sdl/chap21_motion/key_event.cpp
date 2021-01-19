#include "key_event.h"

// >>>>>>>> Key <<<<<<<<
KeyHandler::KeyHandler()
{
    key_states = NULL;
}

KeyHandler::~KeyHandler()
{
    key_states = NULL;
}

void KeyHandler::handleKey()
{
    key_states = SDL_GetKeyboardState( NULL );
    
    if( key_states[ SDL_SCANCODE_UP ] )
    {
        printf("UP KEY\n");
    }
    else if( key_states[ SDL_SCANCODE_DOWN ] )
    {
        printf("DOWN KEY\n");
    }
    else if( key_states[ SDL_SCANCODE_LEFT ] )
    {
        printf("LEFT KEY\n");
    }
    else if( key_states[ SDL_SCANCODE_RIGHT ] )
    {
        printf("RIGHT KEY\n");
    }
    else if( key_states[SDL_SCANCODE_P] )
    {
        if (global_timer.isPaused())
        {
            global_timer.resume();
            printf("Resume \n");
        }
        else
        {
            global_timer.pause();
            printf("Paused\n");
        }
    }
    else if( key_states[SDL_SCANCODE_S])
    {
        // switch between start and stop
        if ( global_timer.isStarted() )
            global_timer.stop();
        else
            global_timer.start();
    }
    else
        return;
}

// >>>>> event key handler <<<<<<
void EventKeyHandler::handleKey(SDL_event *e)
{
    switch(e->type)
    {
        case SDL_KEYDOWN:
            switch(e->key.keysym.sym)
            {
                case SDLK_LEFT:
                    printf("left\n");
                    break;
                case SDLK_RIGHT:
                    printf("right\n");
                    break;
                default:
                    break;
            }
            break;
        case SDL_KEYUP:
            break;
        default:
            break;
    }
}