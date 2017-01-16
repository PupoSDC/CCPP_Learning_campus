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

char** readfile  ( char **words,  char *inputfile,  int *numberoflines);
int    writefile ( char **words,  char *outputfile, int *numberoflines);
char*  reorganize( char *line);

int main(int argc, char *argv[]) {

    if (argv[1] == NULL)                                   // IF argument
    {
        printf("please pass a file name as argument");         // Complains if no argument provided
        return 0;                                              // Finishes the program
    }
    else                                                   // Else
    { 
        printf("parsing: %s \n", argv[1] );                   // Starting program message
    }

    char **words;                                          // Allocates an array of strings

    int numberoflines;                                     // Declares variable for number of lines
    words = readfile( words, argv[1], &numberoflines);     // Reads the array of strings from file

    if ( numberoflines < 1 ){
        printf("error reading file! \n"); 
        return 0; 
    }                   

    for (int i = 0; i < numberoflines; i++)                // For every line read
    {
        strcpy(words[i],reorganize(words[i]));
    }

    writefile(words, argv[1], &numberoflines);

    return 0;
}


// reorganizes a line by size of char
char* reorganize(char *line) {
 
    char **words;                                             // Declare array with words
    char *word;                                               // Declare variable for single word
    char *response = malloc( strlen(line) * sizeof(char));    // Declare and allocate response string

    int  numberofwords = 1;                                   // Atleast one word in the list

    for ( int i = 0; i < strlen(line); i++)                   // Count words based on spaces
    { 
        if(line[i] == ' ') numberofwords++;                       // Increment counter
    }
    
    words = malloc(numberofwords*sizeof(char *));             // Allocate memory based on number of words

    for( int i = 0; i < numberofwords; i++)                   // For each word
    {   
        word     = strsep(&line, " ");                            // Separete word base on spaces
        words[i] = malloc(sizeof(char)*(strlen(word) + 1));       // Allocate memory for the word
        strcpy(words[i],word);                                    // Copy word to array
    }; 

    strcpy(response, words[numberofwords-1] );                // Copy last word to response

    for (int i = numberofwords -2; i > -1; i-- )              // For every other word
    {
        strcat(response," ");                                    // Add a space
        strcat(response,words[i]);                               // Add a word
    } 

    return response;                                          // Return response
}

// Reads a file, returns an array of strings. modifies by reference a number of lines
char** readfile(char **words, char *inputfile, int *numberoflines) {

    char  filename[100];                               // Declares new string            
    strcpy(filename,inputfile);                        // Copys the string to preserve orignal string
    strcat(filename,".in");                            // Adds  extension to file name

    FILE *file;                                        // Alocate file memory
    file = fopen(filename, "r");                       // Open file with read permission
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

// Write a file
int writefile(char **words, char *outputfile, int *numberoflines) {

    char  filename[100];                               // Declares new string            
    strcpy(filename,outputfile);                       // Copys the string to preserve orignal string
    strcat(filename,".out");                           // Adds  extension to file name
 
    FILE *file;                                        // Alocate file memory
    file = fopen(filename, "w");                       // Open file with write permission
    if (file == NULL) return -1;                       // If no file return -1

    for (int i = 0; i < *numberoflines; i++)           // For every line
    {
        fprintf(file, "Case #%d: %s\n",i+1,words[i]);                        
    } 

    printf("File  %s, written with sucess! \n", outputfile);
    return 0;

}