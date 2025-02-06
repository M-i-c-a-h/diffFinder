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
void printAligned(const std::string& lhs, const std::string& rhs);
void displayWelcomeMessage();

int main()
{
    startup(); // function to prepare system settings
    displayWelcomeMessage();

    vector<string> List1, List2;
    string input;
    std::cout << "Paste Original text:(type 'GO!' to finish) || type '-quit' to terminate\n";
    while ( std::getline ( std::cin, input ) )
    {
        if (input == "GO!") {
            break; // GO input when 'GO' is encountered
        }
        else if ( input == "-quit" ) {
            return 0;    
        }
        List1.push_back ( input );
    }
    
    std::cout << std::endl;
    std::cout << "Paste New text:(type 'GO!' to finish || type '-quit' to terminate)\n";
    while ( std::getline ( std::cin, input ) )
    {
        if (input == "GO!") {
            break; // GO input when 'GO' is encountered
        }
        else if ( input == "-quit" ) {
            return 0;    
        }
        List2.push_back ( input );
    }
        
    processData1 ( List1, List2 );

    std::cout << std::endl;
    return 0;
}

void processData ( const string& LHS, const string& RHS )
{
    std::cout << "Analzing difference ........\n";

    vector<HighlightedWord> _lhs , _rhs;
    
    _lhs = splitWords ( LHS );
    _rhs = splitWords ( RHS );

    findDifference ( _lhs, _rhs );
    displayResult ( _lhs, _rhs );

}

void processData1 ( const vector<string>& LHS, const vector<string>& RHS )
{
    std::cout << "Analzing difference ........\n";
    printAligned ( "     LHS     ", "     RHS     " );

    vector<vector<HighlightedWord>> _lhs , _rhs;
    
    _lhs = splitWords ( LHS );
    _rhs = splitWords ( RHS );

    processDiffPerLine ( _lhs, _rhs );
    processDisplay ( _lhs, _rhs );

}

void displayWelcomeMessage()
{
    horizontalBorder(); 
    horizontalBorder(); 
    printAlign( CENTER, "WELCOME TO DIFF FINDER" ); 
    std::cout << std::endl;
    //horizontalBorder(); 
    //horizontalBorder(); 
    std::cout << std::endl;
}
