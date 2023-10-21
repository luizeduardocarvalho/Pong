#include <stdio.h>
#include <termios.h>
#include <unistd.h>

class BufferToggle
{
    public:
        void off()
        {
            tcgetattr(STDIN_FILENO, &t); //Get the current terminal I/O structure
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }

        void on(void)
        {
            tcgetattr(STDIN_FILENO, &t);
            t.c_lflag |= ICANON;
            tcsetattr(STDIN_FILENO, TCSANOW, &t);
        }
        
    private:
        struct termios t;
};
