#ifndef _H_TIMER
#define _H_TIMER

#include <SDL2/SDL.h>
#include <stdio.h>

class Timer
{
    public:
        // init
        Timer();

        // various action
        void start();
        void stop();
        void pause();
        void resume();

        // Gets the timer's time
        Uint32 getTicks();
        Uint32 getTrueTicks();

        // checks the status
        bool isStarted();
        bool isPaused();

    private:
        // record the start ticks
        Uint32 start_ticks;
        // record the last point to pause
        Uint32 latest_ticks;
        // the past time
        Uint32 flow_ticks;

        // timer status
        bool is_paused;
        bool is_started;
};

#endif