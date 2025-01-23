#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <iomanip>
#include <sys/ioctl.h>
#include <SFML/Window.hpp>

static unsigned int HORIZONTAL = 100;
static unsigned int VERTICAL = 80;
enum Position{ LEFT, CENTER, RIGHT };

void GetUserDesktopResolution();
void setTerminalWidth();
void printAlign( Position pos, std::string s );

void startup()
{
    //GetUserDesktopResolution();
    setTerminalWidth();
}

// create a single Horizontal border [---------] with ternimal size
void horizontalBorder()
{
    std::cout << std::setfill('=') << std::setw(HORIZONTAL) << "=" << std::endl;
}

void verticalBorder()
{
    std::cout << "||";
}

int main()
{
    startup(); // function to prepare system settings

    horizontalBorder(); 
    horizontalBorder(); 
    verticalBorder();   std::cout << std::endl;
    verticalBorder();   printAlign( CENTER, "WELCOME TO DIFF FINDER" ); 

    return 0;
}

// Get the horizontal and vertical screen sizes in pixel
void GetUserDesktopResolution()
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    HORIZONTAL = modes[0].size.x;
    VERTICAL = modes[0].size.y;
}

// Get terminal width - LINUX // TODO:WINDOWS??
void setTerminalWidth() 
{
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    HORIZONTAL = w.ws_col; // Terminal width in columns
    //std::cout << "Your screen is " << HORIZONTAL << " Wide" << std::endl;

}

// function to print with alignment
void printAlign( Position pos, std::string s )
{
    int spaces = 0;
    switch( pos )
    {
      case CENTER : 
        spaces = ( HORIZONTAL - s.size() - 2) / 2; 
        break;
      case RIGHT  : 
        spaces =   HORIZONTAL - s.size() - 3; 
        break;
      case LEFT   : 
        std::cout << " ";
        break;
    }
    
    if (spaces > 0) {
        std::cout << std::string(spaces, ' '); // Print spaces before the text
    }

    std::cout << s; // Print the actual text

    std::cout << std::endl; // Closing vertical border and newline 
}
