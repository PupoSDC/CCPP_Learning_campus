/*
    problem: https://code.google.com/codejam/contest/351101/dashboard#s=p1

    Given a list of space separated words, reverse the order of the words. 
    Each line of text contains L letters and W words. 
    A line will only consist of letters and space characters. 
    There will be exactly one space character between each pair of consecutive words.
    
    compile: gcc main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>   

char** readfile(char** words, const char* inputfile, int*numberoflines);
char*  reorganize(char *line);

int main() {

    const char *inputfile = "B-small-practice.in";         // Allocates name of the read file

    char **words;                                          // Allocates an array of strings

    int numberoflines;
    words = readfile( words, inputfile, &numberoflines);   // Reads the array of strings from file

    if ( numberoflines < 1 ) return 0;                     // If no read lines finishes the program

    for (int i = 0; i < numberoflines; i++)                // For every line read
    {
        printf("before: %s \n", words[i] );    
        reorganize(words[i]);                     // Print the line      
        //printf("after: %s \n",  reorganize(words[i]) );                         // Print the line        
    }

    return 0;
}


// reorganizes a line by size of char
char* reorganize(char *line) {
 
    char **words; 
    char *word;                                     
    char *response;

    int  numberofwords = 1; // Atleast one word in the list
    int  i             = 0; // Loop variable
    int  j             = 0; // Loop variable

    for ( i = 0; i < strlen(line); i++)
    {
        if(line[i] == ' ') numberofwords++;
    }
    
    words = malloc( sizeof(char*) * (numberofwords + 1) );
    
    for( i = 0; i < numberofwords; i++)
    {   
        word = strsep(&line, " ");
        strcpy(words[j],word);  
    }

    strcpy(response, words[0]);

    //printf("after: %s \n",  response );

    /*
    for (i = numberofwords -2; i > 0; i-- )
    {
        strcat(response," ");
        strcat(response,words[i]);
    } */

    return response;
}

// Reads a file, returns an array of strings. modifies by reference a number of lines
char** readfile(char **words, const char *inputfile, int *numberoflines) {

    FILE *file;                                        // Alocate file memory
    file = fopen(inputfile, "r");                      // Open file with read permission
    if (file == NULL)                                  // If no file
    {   
        *numberoflines = 0;                                // Set number of lines to 0
        return words;                                      // Return
    } 
    
    int     line_length;                               // Length of a single line
    char    line[1000];                                // Buffer for each line
 
    fgets (line, sizeof(line), file);                  // reads first line

    *numberoflines = atoi(line);                       // Stores the number of lines

    words = malloc((*numberoflines)*sizeof(char *));   // Allocate an array of pointers to strings

    if (words == NULL)                                 // If no allocation return 0 lines read
    {
        *numberoflines = 0;                                // Set number of lines to 0
        return words;                                      // Return
    } 

    for (int i = 0; i < *numberoflines; i++)           // For every line
    {
        fgets(line, sizeof(line), file);                   // Gets a line  

        line_length = strlen(line);                        // Defines the line length
        line[line_length - 1] = '\0';                      // Removes /n
        line_length--;                                     // Updates line lenght

        words[i] = malloc(sizeof(char)*(line_length + 1)); // Allocates line memory in array
        strcpy(words[i], line);                            // Stores line in array
    } 

    fclose(file);                                     // Closes file
    return words;                                     // Returns number of lines read
}