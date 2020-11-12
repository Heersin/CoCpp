#ifndef _H_KEY_EVENT
#define _H_KEY_EVENT

#include <SDL2/SDL.h>
#include <iostream>
#include "timer.h"
// global timer in main.cpp
// Timer class defined in timer.h
extern Timer global_timer;

// >>>>>>>>>>>>>>> Key Wrapper <<<<<
class KeyHandler
{
    public:
        KeyHandler();
        ~KeyHandler();
        void handleKey();
    private:
        // this function will return a pointer to an SDL lib internal array
        // do not free it manually
        const Uint8 *key_states;
};


#endif