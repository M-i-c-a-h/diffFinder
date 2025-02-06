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
int getTerminalWidth();
void setTerminalWidth();
void printAlign( Position pos, std::string s );
void printChunk(const std::string& str, int width);
void printAligned(const std::string& lhs, const std::string& rhs);

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


int main2()
{
    startup(); // function to prepare system settings

    horizontalBorder(); 
    horizontalBorder(); 
    std::cout << std::endl;
    printAlign( CENTER, "WELCOME TO DIFF FINDER" ); 

    std::cout << std::left << std::setw(HORIZONTAL / 2) << "-----LHS-----" << " | " << "-----RHS-----" << std::endl;

    // Example entries
    printAligned("1) This is a very long LHS entry that spans multiple lines to demonstrate chunking", 
                 "This is a very long RHS entry that also spans multiple lines for demonstration");

    printAligned("2) Short LHS", "Short RHS");

    printAligned("3) Another long LHS entry that spans multiple lines for chunking", 
                 "Another long RHS entry to test the multi-line logic");
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
}

// Get terminal width - LINUX // TODO:WINDOWS??
int getTerminalWidth() 
{
    return HORIZONTAL;
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
        spaces = (  HORIZONTAL / 4 ) - s.size() - 3; // 3 => separator  
        break;
      case LEFT   : 
        spaces = (  HORIZONTAL / 4 ) - s.size() - 3; // 3 => separator  
        break;
    }
    
    if (spaces > 0) {
        std::cout << std::string(spaces, ' '); // Print spaces before the text
    }

    std::cout << s; // Print the actual text

    //std::cout << std::endl; // Closing vertical border and newline 
}

// Function to print a portion of a string up to the specified width
void printChunk(const std::string& str, int width) {
    if (str.size() <= width) 
    {   
        std::cout << std::left << std::setfill(' ') << std::setw(width) << str;
    } 
    else 
    {
        std::cout << std::left << std::setfill(' ') << std::setw(width) << str.substr(0, width);
    }
}

// Function to align and print LHS and RHS across multiple lines
void printAligned(const std::string& lhs, const std::string& rhs) {
    
    int spaces = 20;  
    std::cout << std::string(spaces, ' '); // Print spaces before the text
    std::cout << lhs; // Print the actual text

    size_t sectionWidth = HORIZONTAL / 2;
    std::cout << std::string( sectionWidth - spaces - lhs.size() , ' '); // Print spaces before the text

    std::cout << std::string(spaces, ' '); // Print spaces before the text
    std::cout << rhs; // Print the actual text
    std::cout << std::endl;
    /*
    size_t lhsStart = 0, rhsStart = 0;
    
    const int totalWidth = HORIZONTAL;  // Total width of the output line
    const int lhsWidth = ( HORIZONTAL / 2);   // Width allocated for LHS
    const int rhsWidth = totalWidth - lhsWidth - 3; // Width for RHS (total - LHS - separator)

    while (lhsStart < lhs.size() || rhsStart < rhs.size()) {
        // Extract chunks of LHS and RHS up to their respective widths
        std::string lhsChunk = lhs.substr(lhsStart, lhsWidth);
        std::string rhsChunk = rhs.substr(rhsStart, rhsWidth);

        // Print the chunks with padding and separator
        printChunk(lhsChunk, lhsWidth);
        std::cout << " | ";
        printChunk(rhsChunk, rhsWidth);

        // Move to the next chunk
        lhsStart += lhsWidth;
        rhsStart += rhsWidth;

        // End the current line
        std::cout << std::endl;
    }
    */

}
