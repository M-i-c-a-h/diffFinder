#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <iomanip>

#include "display.cpp"
#define TIME 30000

using namespace std;

static const char* colorScheme[3] = { "\033[0m", "\033[101m", "\033[102m" }; // { RESET, RED, GREEN }
static int maxChar = 0;

// structure for Highlighted word
struct HighlightedWord
{
    string word;
    bool highlight;
};

// function to split words
vector<HighlightedWord> splitWords (const string& word )
{
    vector<HighlightedWord> words;
    stringstream ss (word);
    string _word;

    while ( ss >> _word )
    {
        words.push_back ( { _word, false } ); // create instance of HighlightedWord
    }

    return words;
}
// function to split multiple line
vector<vector<HighlightedWord>> splitWords (const vector<string>& inputLines )
{   
    vector<vector<HighlightedWord>> List;
    
    for ( const auto& line : inputLines )
    {
        stringstream ss ( line );
        string _word;
        vector<HighlightedWord> words;

        while ( ss >> _word )
        {
            words.push_back ( { _word, false } ); // create instance of HighlightedWord
        }
        List.push_back ( words );
    }

    return List;
}
// function to find and highlight differences
void findDifference ( vector<HighlightedWord>& LHS_Words, vector<HighlightedWord>& RHS_Words )
{   
    // compare and highlight min length of words
    int minLength = min ( LHS_Words.size(), RHS_Words.size() );
    int charSize = 0;

    for ( int i = 0; i < minLength; i++ )
    {
        charSize = LHS_Words[i].word.size();
        maxChar =  max ( maxChar, charSize );

        if ( LHS_Words[i].word != RHS_Words[i].word )
        {
            LHS_Words[i].highlight = RHS_Words[i].highlight = true; // highlight LHS & RHS word
        }
    }
    
    // Highlight all extra words in LHS_Words
    for ( int i = minLength; i < LHS_Words.size(); i++ )
    {
        charSize = LHS_Words[i].word.size();
        maxChar =  max ( maxChar, charSize );
        LHS_Words[i].highlight = true;
    }

    // Highlight all extra words in RHS_Words
    for ( int i = minLength; i < RHS_Words.size(); i++ )
    {
        RHS_Words[i].highlight = true;
    }
}

// function to process differences per line
void processDiffPerLine ( vector<vector<HighlightedWord>>& List1, vector<vector<HighlightedWord>>& List2 )
{   
    for ( int i = 0; i < min ( List1.size() , List2.size() ); i++ )
    {
        findDifference ( List1[i], List2[i] );
    }

    std::vector<HighlightedWord> empty;
    // process additional lines in List1
    for ( int i = List2.size(); i < List1.size(); i++ )
    {
        findDifference ( List1[i], empty );
    }
    
    // process additional lines in List2
    for ( int i = List1.size(); i < List2.size(); i++ )
    {
        findDifference ( empty, List2[i] );
    }

}
/*
// function to display result
void displayResult ( vector<HighlightedWord> LHS_Words, vector<HighlightedWord> RHS_Words )
{ 
    std::string lhsText, rhsText;

    // build lhsText with [color scheme "RED"]
    for (const auto& word : LHS_Words )
    {
        if ( word.highlight )
        {
            //lhsText += colorScheme[1] + word.word + colorScheme[0] + " ";
            //lhsText += word.word + " ";
            cout << colorScheme[1] << word.word << colorScheme[0] << " ";
        }
        else
        {
            //lhsText += word.word + " ";
            std::cout << word.word << " ";
        }
    }
    
    std::cout << "     |     ";

    // build rhsText with  [color scheme "GREEN"]
    for (const auto& word : RHS_Words )
    {   
        if ( word.highlight )
        {
            //rhsText += colorScheme[2] + word.word + colorScheme[0] + " ";
            //rhsText += word.word + " ";
            std::cout << colorScheme[2] << word.word << colorScheme[0] << " ";
        }
        else
        {
            //rhsText += word.word + " ";
            std::cout << word.word << " ";
        }
    }
    // Align and print LHS and RHS using the printAligned function

    //printAligned(lhsText, rhsText);
    std::cout << endl;
}
*/
void displayResult( vector<HighlightedWord> LHS_Words, vector<HighlightedWord> RHS_Words) {
    const int totalWidth =  getTerminalWidth();     // Total width of the terminal
    const int sectionWidth = totalWidth / 2;        // Width of each section (LHS and RHS)
    int lhsWidth = 0, rhsWidth = 0;                 // Current line widths for LHS and RHS

    size_t lhsIndex = 0, rhsIndex = 0;
    while (lhsIndex < LHS_Words.size() || rhsIndex < RHS_Words.size()) {
        int lhsWidth = 0, rhsWidth = 0; // Current line widths for LHS and RHS

        // LHS Section
        while (lhsIndex < LHS_Words.size() && lhsWidth + LHS_Words[lhsIndex].word.size() + 1 <= sectionWidth) {
            const auto& word = LHS_Words[lhsIndex];
            if (word.highlight) {
                std::cout << "\033[31m" << word.word << "\033[0m ";
            } else {
                std::cout << word.word << " ";
            }
            lhsWidth += word.word.size() + 1; // Word length + space
            ++lhsIndex;
        }

        // Pad remaining space in LHS if we've exhausted words
        std::cout << std::string(sectionWidth - lhsWidth, ' ');

        // Separator
        std::cout << " | ";

        // RHS Section
        while (rhsIndex < RHS_Words.size() && rhsWidth + RHS_Words[rhsIndex].word.size() + 1 <= sectionWidth) {
            const auto& word = RHS_Words[rhsIndex];
            if (word.highlight) {
                std::cout << "\033[32m" << word.word << "\033[0m ";
            } else {
                std::cout << word.word << " ";
            }
            rhsWidth += word.word.size() + 1; // Word length + space
            ++rhsIndex;
        }

        // Pad remaining space in RHS if we've exhausted words
        std::cout << std::string(sectionWidth - rhsWidth, ' ') << std::endl;
    }
}

// function to display differences per line
void processDisplay ( vector<vector<HighlightedWord>>& List1, vector<vector<HighlightedWord>>& List2 )
{   
    cout << "-----LHS-----" <<" | " << "-----RHS-----\n";
    int line = 1;
    for ( int i = 0; i < min ( List1.size() , List2.size() ); i++ )
    {
        //std::cout << line++ << ") ";
        displayResult ( List1[i], List2[i] );
    }
    
    std::vector<HighlightedWord> empty;
    // process additional lines in List1
    for ( int i = List2.size(); i < List1.size(); i++ )
    {
        std::cout << line++ << " ";
        displayResult ( List1[i], empty );
    }
    
    // process additional lines in List2
    for ( int i = List1.size(); i < List2.size(); i++ )
    {
        std::cout << line++ << " ";
        displayResult ( empty, List2[i] );
    }

}
