#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <cstdlib>

#include "buffertoggle.cpp"

#define WINDOW_WIDTH 120
#define WINDOW_HEIGHT 35
#define FILLED_SQUARE "\u2588"

struct Bar
{
    int x;
    int y;
    int width;
    int height;
} bar;

void setup_environment()
{
    BufferToggle bt;
    bt.off();

    // sets hight an width of terminal
    std::cout << "\e[8;" 
            << WINDOW_HEIGHT 
            << ";" 
            << WINDOW_WIDTH 
            << "t";

    // hides cursor
    std::cout << "\e[?25l";

    // hides input
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void render_screen(Bar player_bar, Bar enemy_bar)
{
    system("clear");
    
    // render bars
    for (int i = 0; i < player_bar.width; i++)
    {
        for (int j = 0; j < player_bar.height; j++)
        {
            std::cout << "\e[" << player_bar.y + j << ";" << player_bar.x + i << "H";
            std::cout << FILLED_SQUARE;
        }
    }

    for (int i = 0; i < enemy_bar.width; i++)
    {
        for (int j = 0; j < enemy_bar.height; j++)
        {
            std::cout << "\e[" << enemy_bar.y + j << ";" << enemy_bar.x + i << "H";
            std::cout << FILLED_SQUARE;
            // for red \33[31m
        }
    }
}

void process_input(std::string user_input, Bar& bar)
{
    if (user_input == "w")
    {
        bar.y--;
    }
    else if (user_input == "s")
    {
        bar.y++;
    }
    else if (user_input == "a")
    {
        bar.x--;
    }
    else if (user_input == "d")
    {
        bar.x++;
    }
}

int main(void)
{
    setup_environment();

    Bar player_bar = { 5, -1, 1, 9 };
    player_bar.y = WINDOW_HEIGHT / 2 - player_bar.height / 2;

    Bar enemy_bar = { 115, -1, 1, 9 };
    enemy_bar.y = WINDOW_HEIGHT / 2 - enemy_bar.height / 2;

    std::string user_input = "a";
    while ((user_input) != "q")
    {
        process_input(user_input, player_bar);
        render_screen(player_bar, enemy_bar);
        user_input = std::getchar();
    }

    return EXIT_SUCCESS;
}
