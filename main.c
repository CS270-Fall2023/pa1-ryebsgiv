/**
 * @file main.c
 * @author Ben Givens
 * @brief  A program that uses a function that will parse a string into tokens (or words), similar to what the shell is required to do.
 * @date 2023-09-14
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int getTokens(char *s, char ***args);

int main() {
    // Define variables. arrayOfTokens will hold the address of the tokens.
    char **arrayOfTokens = NULL;
    char userString[100];
    // Define the number of tokens for later.
    int numberOfTokens;

    // Ask the user for their string and get the answer.
    printf("Please enter the string you wish to have parsed.\n");
    fgets(userString, sizeof(userString), stdin);

    // Call the function.
    numberOfTokens = getTokens(userString, &arrayOfTokens);
    
    // Check if the function encountered an error.
    if (numberOfTokens == -1) {
        printf("There was a problem allocating memory for your tokens.\n");
        return 1;
    }

    // Print the number of tokens and the tokens.
    printf("The number of tokens is %d.\n", numberOfTokens);
    for (int i = 0; i < numberOfTokens; i++) {
        printf("Token %d: %s\n", i+1, arrayOfTokens[i]);
        free(arrayOfTokens[i]);
    }
    free(arrayOfTokens);

    return 0;
}
