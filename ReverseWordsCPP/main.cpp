#include <iostream>
#include <string>
#include "Words.h"
using namespace std;


int main(int argc, char *argv[]) {

    if (argv[1] == NULL)                                            // IF argument
    {
        cout << "please pass a file name as argument \n";               // Complains if no argument provided
        return 0;                                                       // Finishes the program
    }
    else                                                            // Else
    { 
        cout << "parsing: " << argv[1] << "\n";                         // Starting program message
    }


    int numberoflines;                                              // Declares variable for number of lines

    Words words;                                                    // Words object declaration

    numberoflines = words.readfile( argv[1] );                      // Reads the array of strings from file


    if ( numberoflines < 1 ) 										// If no lines read
    {
        cout << "please pass a file name as argument \n";               // Complains if no argument provided
        return 0; 														// Finishes the program
    }                   

    words.reorganize();												// Reorganize words 
    
    words.writefile( argv[1] );										// Write output file

    return 0;
}
