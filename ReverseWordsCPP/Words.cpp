#include "Words.h"
#include <iostream>
#include <fstream>
using namespace std;

int  Words::readfile(string inputfile)                                // Readsfile, returns number of lines
{    
    int     line_length;                                                     // Length of a single line
    string  line;                                                            // Buffer for each line
 
	ifstream file((inputfile + ".in").c_str());     					     // Open file
   
 	if (file.is_open())														 // If file is open
	{
		getline (file,line);                                                     // reads first line

	    numberoflines = stoi(line);                                              // Stores the number of lines
	    
	    for (int i = 0; i < numberoflines; i++)                                  // For every line
	    {
	        getline (file,line);                                                     // Gets a line  
	        lines.push_back(line);													 // Push line into vector
	    } 

		file.close();															 // Close file
		return numberoflines;													 // Return number of lines written
	} 
  	else
  	{
  		cout << "Unable to read file";											 // Print failure
        numberoflines = 0;                                                       // Set number of lines to 0
        return 0;																 // Return 0 lines read
  	} 
    
	return numberoflines;									 	             // Return number of lines
}      



int  Words::writefile(string outputfile)                              // Writes file, returns number of lines
{
	
	ofstream file((outputfile + ".out").c_str());     					    // Open file                                                          

 	if (file.is_open())														// If file is open
	{
	    
	    for (int i = 0; i < numberoflines; i++)                                 // For every line
	    {
	        file << "Case #" << i+1 << ": " << lines[i] << "\n";              	    // Write down words	
	    } 

		cout << "File " << outputfile << " written with sucess! \n";            // Print sucess to console
		file.close();															// Close file
		return numberoflines;													// Return number of lines written
	}
  	else
  	{
  		cout << "Unable to write file";											// Print failure
  		return 0;																// Return 0
  	} 
    
}  

void Words::reorganize()                                         // Reorganizes words 
{	

    for(int i = 0; i < lines.size(); i++ )                               // For each line
    {

    	int numberofwords = 0;                                   			// Iterator for number of words
    	vector<string> wordlist;                                            // Vector with lines

    	wordlist.push_back("");                                             // Initialize first word
	
    	for ( int j = 0; j < lines[i].size(); j++)                  	    // Go through every char in string
	    { 

	        if(lines[i][j] == ' ')											// If char is space
	        {
	        	numberofwords++;   												// Count one more word
	        	wordlist.push_back("");    									    // Initialize word
	        }                            
	        else															// Else
	        {
	        	wordlist[numberofwords] = wordlist[numberofwords] + lines[i][j];  // push char to string
	        } 
            
	    } 
	    
	    lines[i] = wordlist[numberofwords];                                  // add last word as first

	    for (int j = numberofwords - 1; j > -1; j--)                         // For the remaining words
	    { 
	    	lines[i] = lines[i] + " " + wordlist[j];                              // add word in rever order
	    } 	    
		
    } 

	return;
} 				    