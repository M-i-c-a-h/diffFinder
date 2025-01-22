#include "diffFinder.cpp"

// function prototypes
vector<HighlightedWord> splitWords (const string& word );
vector<vector<HighlightedWord>> splitWords (const vector<string>& inputLines );
void findDifference ( vector<HighlightedWord>& LHS_Words, vector<HighlightedWord>& RHS_Words );
void displayResult ( vector<HighlightedWord> LHS_Words, vector<HighlightedWord> RHS_Words );
void processData ( const string& LHS, const string& RHS );
void processData1 ( const vector<string>& LHS, const vector<string>& RHS );
void processDisplay ( vector<vector<HighlightedWord>>& List1, vector<vector<HighlightedWord>>& List2 );
void processDiffPerLine ( vector<vector<HighlightedWord>>& List1, vector<vector<HighlightedWord>>& List2 );

int main()
{
    std::cout << "\n\n";
    std::cout << "------ WELCOME TO DIFF FINDER -------" << endl;
    /*
    vector<HighlightedWord> sample1, sample2;
    sample1 = splitWords ( "Today is I created this simple application" );
    sample2 = splitWords ( "Today is we created thiS simple app" );

    findDifference ( sample1, sample2 );
    displayResult ( sample1, sample2 );
    
    std::cout << std::endl;
    */

    vector<string> List1, List2;
    string input;
    std::cout << "Paste Original text:(type 'GO!' to finish)\n";
    while ( std::getline ( std::cin, input ) )
    {
        if (input == "GO!") {
            break; // GO input when 'GO' is encountered
        }
        List1.push_back ( input );
    }
    
    std::cout << "Paste New text:(type 'GO!' to finish)\n";
    while ( std::getline ( std::cin, input ) )
    {
        if (input == "GO!") {
            break; // GO input when 'GO' is encountered
        }
        List2.push_back ( input );
    }
        
    processData1 ( List1, List2 );
    
    std::cout << std::endl;
    return 0;
}

void processData ( const string& LHS, const string& RHS )
{
    std::cout << "Analzing difference ........\n\n";

    vector<HighlightedWord> _lhs , _rhs;
    
    _lhs = splitWords ( LHS );
    _rhs = splitWords ( RHS );

    findDifference ( _lhs, _rhs );
    displayResult ( _lhs, _rhs );

}

void processData1 ( const vector<string>& LHS, const vector<string>& RHS )
{
    std::cout << "Analzing difference ........\n\n";

    vector<vector<HighlightedWord>> _lhs , _rhs;
    
    _lhs = splitWords ( LHS );
    _rhs = splitWords ( RHS );

    processDiffPerLine ( _lhs, _rhs );
    processDisplay ( _lhs, _rhs );

}
