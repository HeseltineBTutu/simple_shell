#include "main.h"

/**
 * free_tokens - Free memory allocated for tokens
 * 
 * @tokens: The array of tokens to free
 * @token_count: The number of tokens in the array
*/
void free_tokens(char **tokens, int token_count)
{
    int i;

    for (i = 0; i < token_count; i++)
    {
        free(tokens[i]);
        tokens[i] = NULL;
    }
}