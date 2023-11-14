#include "main.h"

/**
 * cleanup_tokens - Free memory allocated for tokens
 *
 * @tokens: The array of tokens to be cleaned up
 * @token_count: The number of tokens in the array
 */
void cleanup_tokens(char **tokens, int token_count)
{
	int i;

	for (i = 0; i < token_count; i++)
	{
		free(tokens[i]);
		tokens[i] = NULL;
	}
}
