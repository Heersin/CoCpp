#ifndef _H_DOT
#define _H_DOT

class Dot
{
    public:
        static const int DOT_WIDTH = 20;
        static const int DOT_HEIGHT = 20;

        static const int DOT_VEL = 10;

        // constructor
        Dot();

        // handle key press
        void handleEvent( SDL_event &e);

        // functionalities
        void move();

        // show the dot on the screen
        void render();

    private:
        int x_pos, y_pos;
        int vel_x, vel_y;
}

#endif