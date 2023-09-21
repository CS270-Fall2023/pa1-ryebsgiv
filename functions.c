/**
 * @file functions.h
 * @author Ben Givens
 * @brief header file for getTokens function
 *  @date 2023-09-14
 */
#include "functions.h"

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
    char *tokenStart = s; //assign a pointer to the input string

    // Allocate memory for the tokens using the previously set highest limit
    *args = (char **)malloc(sizeof(char *) * numberOfPossibleTokens);
    //check if tokens allocated properly
    if (args == NULL) {
        printf("There was a bad allocation when setting up the token size\n");
        return -1;
    }
    
    //Start going through the string
    int letters=-1; //Variable used to bypass spaces at the very beginning of the string. Example "  Hello". This variable will be negative until the 'H'.
    int i=0;
    while(i<numberOfPossibleTokens) 
    {
        //Checks if the letters have begun in the string
        if (s[i]!=' ')
        {
            letters=1;
        }
        if (letters!=1)
        {
            tokenStart = &s[i + 1];
        }

        //Checls for the scenario that there is only one token and no other information in the string. 
        if (s[i]=='\0'&& numberToken==0){
            (*args)[numberToken] = malloc(strlen (tokenStart)+1);
            if ((*args)[numberToken] == NULL) 
            {
                printf("There was a bad memory allocation when a new token was added to tokens\n");
                return -1;
            }
            strcpy((*args)[numberToken],tokenStart);
            numberToken++; //increase the token count
            //Check if the number of tokens is within our bounds
            if (numberToken >= numberOfPossibleTokens) {
                printf("Went over the token limit\n");
                break;
            }

            //Increase the character count
            tokenStart = &s[i + 1];
            }

        //Breaks up strings into tokens by seperating by spaces.
        if (s[i] == ' ' && s[i+1]!=' ' && letters==1) 
        {   
            //Sets the last value in the token as NULL
            s[i] = '\0';

            //Allocate memory for the token
            (*args)[numberToken] = malloc(strlen (tokenStart)+1);
            if ((*args)[numberToken] == NULL) 
            {
                printf("There was a bad memory allocation when a new token was added to tokens\n");
                return -1;
            }
            strcpy((*args)[numberToken],tokenStart);
            numberToken++; //increase the token count
            //Check if the number of tokens is within our bounds
            if (numberToken >= numberOfPossibleTokens) {
                printf("Went over the token limit\n");
                break;
            }

            //Increase the character count
            tokenStart = &s[i + 1];

        }
        //This is the conditional check to see if the string ends without a space
        if (s[i+1]=='\0'){
            (*args)[numberToken] = malloc(strlen (tokenStart)+1);
            if ((*args)[numberToken] == NULL) 
            {
                printf("There was a bad memory allocation when a new token was added to tokens\n");
                return -1;
            }
            strcpy((*args)[numberToken],tokenStart);
            numberToken++;
            break;
        }
        i++;
    }
    //Create a token at the end of the tokens array which is NULL
    //Sets the last value in the token as NULL
    if ((*args)[numberToken] != NULL) {
            //Allocate memory for the token and copy 
            (*args)[numberToken] = malloc(strlen (tokenStart)+1);
            (*args)[numberToken]=NULL;
            if ((*args)[numberToken] != NULL) {
                printf("There was a bad memory allocation when the final token was added to tokens\n");
                return -1;
            }
    }

    return numberToken;
}