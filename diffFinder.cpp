#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unistd.h>
#include <iomanip>

using namespace std;

#define TIME 30000
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

// function to display result
void displayResult ( vector<HighlightedWord> LHS_Words, vector<HighlightedWord> RHS_Words )
{ 
    const int COLUMN_WIDTH = maxChar;
    int current_width = 0; // To track the width of the current LHS line
    
    // print LHS [color scheme "RED"]
    for (const auto& word : LHS_Words )
    {
        if ( word.highlight )
        {
            cout << colorScheme[1] << word.word << colorScheme[0] << " ";
        }
        else
        {
            cout << word.word << " ";
        }
        current_width += word.word.length() + 1; // +1 for the space
    }
    
    std::cout << "     |     ";

    // print RHS [color scheme "GREEN"]
    //cout << "-----RHS-----\n";
    for (const auto& word : RHS_Words )
    {   
        if ( word.highlight )
        {
            cout << colorScheme[2] << word.word << colorScheme[0] << " ";
        }
        else
        {
            cout << word.word << " ";
        }
    }
    cout << endl;
}

// function to display differences per line
void processDisplay ( vector<vector<HighlightedWord>>& List1, vector<vector<HighlightedWord>>& List2 )
{   
    cout << "-----LHS-----" <<" | " << "-----RHS-----\n";
    int line = 1;
    for ( int i = 0; i < min ( List1.size() , List2.size() ); i++ )
    {
        std::cout << line++ << ") ";
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
