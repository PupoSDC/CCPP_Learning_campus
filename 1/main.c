#include <stdio.h>
#include <stdlib.h>
#include <string.h>   

int readfile(char** words, const char* inputfile);


int main() {

    const char *inputfile = "B-small-practice.in";     // Allocates name of the read file

    char **words;                                      // Allocates an array of strings

    int numberoflines = readfile( words, inputfile);   // Reads the array of strings from file

    if ( numberoflines < 1 ) return 0;                 // If no read lines finishes the program

/*
    for (int i = 0; i < numberoflines; i++)            // For every line read
    {
        printf("%s /n", words[i] );                         // Print the line        
    }
*/

    return 0;
}


int readfile(char **words, const char *inputfile) {

    FILE *file;                                     // Alocate file memory
    file = fopen(inputfile, "r");                   // Open file with read permission
    if (file == NULL) return 0;                     // If no file return 0 lines read
 
    int     numberoflines;                          // Total number of lines
    char    line[1000];                             // Buffer for each line
 
    fgets (line, sizeof(line), file);               // reads first line

    numberoflines = atoi(line);                     // Stores the number of lines

    words = malloc(numberoflines*sizeof(char *));   // Allocate an array of pointers to strings

    if (words == NULL) return 0;                    // If no allocation return 0 lines read

    for (int i = 0; i < numberoflines; i++)         // For every line
    {
        fgets(line, sizeof(line), file);                // Gets a line                      
        words[i] = malloc(strlen(line) + 1);            // Allocates line memory in array
        words[i] = line;                                // Stores line in array
        printf("%s", words[i] );  
    }

    fclose(file);                                   // Closes file

    printf("Retrieved %d lines \n",numberoflines);  // Reports number of lines read

    for (int j = 0; j < numberoflines; j++)         // For every line read
    {
        printf("%s", words[j] );                   
    }

    return numberoflines;                           // Returns number of lines read
}
