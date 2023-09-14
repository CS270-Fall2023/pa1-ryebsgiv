/**
 * @file PA1.c
 * @author Ben Givens
 * @brief  A program that uses a function that will parse a string into tokens (or words), similar to what the shell is required to do.
 * @date 2023-09-14
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("Token %d: %s\n", i + 1, arrayOfTokens[i]);
        free(arrayOfTokens[i]);
    }
    free(arrayOfTokens);

    return 0;
}
/**
 * @brief Parse the users input into tokens and return the total number of tokens
 * 
 * @param s The users string
 * @param args The array of tokens 
 * @return int the number of tokens
 */
int getTokens(char *s, char ***args) {
    //Check if pointers worked
    if (s == NULL || args == NULL) {
        printf("The pointers sent to the function didn't work\n");
        return -1;
    }

    int numberOfPossibleTokens = 100; //I set this as 100, but you could set the value higher for a bigger string
    int numberToken = 0;
    char **tokens = NULL;
    char *tokenStart = s; //assign a pointer to the input string

    // Allocate memory for the tokens using the previously set highest limit
    tokens = (char **)malloc(sizeof(char *) * numberOfPossibleTokens);
    //check if tokens allocated properly
    if (tokens == NULL) {
        printf("There was a bad allocation when setting up the token size\n");
        return -1;
    }
    
    //Start going through the string
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ' && s[i+1]!=' ') 
        {
            //Sets the last value in the token as NULL
            s[i] = '\0';

            // Allocate memory for the token and copy
            //I made a copy here so that I can increase the memory allocation 
            char *copy = malloc(strlen (tokenStart+1));
            if (copy==NULL)
            {
                return -1;
            }
            tokens[numberToken]=strcpy(copy,tokenStart);
            if (tokens[numberToken] == NULL) {
                printf("There was a bad memory allocation when a new token was added to tokens\n");
                return -1;
            }

            numberToken++; //increase the token count

            //Check if the number of tokens is within our bounds
            if (numberToken >= numberOfPossibleTokens) {
                printf("Went over the token limit\n");
                break;
            }

            //Increase the character count
            tokenStart = &s[i + 1];
        }
    }

    // Handle the last token if there's no newline character at the end
    if (s[numberToken- 1] != '\n') {
            // Allocate memory for the token and copy 
            char *copy = malloc(strlen (tokenStart+1));
            if (copy==NULL)
            {
                return -1;
            }
            tokens[numberToken]=strcpy(copy,tokenStart);
        if (tokens[numberToken] == NULL) {
            printf("There was a bad memory allocation when a new token was added to tokens\n");
            return -1;
        }
        numberToken++;
    }

    *args = tokens;

    return numberToken;
}
