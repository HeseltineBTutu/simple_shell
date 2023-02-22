#include "main.h"
/**
 * split_string - splits a string into an array of strings
 * @str: string to split
 * @delim: delimiter characters
 *
 * Return: array of strings or NULL on failure
 */
char **split_string(char *str, const char *delim)
{
    char **tokens = NULL;
    size_t token_count = 0, token_size = 16, len;
    char *token, *saveptr;

    if (str == NULL || delim == NULL)
        return (NULL);

    tokens = malloc(token_size * sizeof(char *));
    if (tokens == NULL)
        return (NULL);

    for (token = strtok_r(str, delim, &saveptr); token != NULL;
         token = strtok_r(NULL, delim, &saveptr))
    {
        if (token_count >= token_size)
        {
            token_size *= 2;
            tokens = realloc(tokens, token_size * sizeof(char *));
            if (tokens == NULL)
                return (NULL);
        }
        len = strlen(token);
        tokens[token_count] = malloc((len + 1) * sizeof(char));
        if (tokens[token_count] == NULL)
            return (NULL);
        strcpy(tokens[token_count], token);
        token_count++;
    }

    if (token_count >= token_size)
    {
        token_size += 1;
        tokens = realloc(tokens, token_size * sizeof(char *));
        if (tokens == NULL)
            return (NULL);
    }
    tokens[token_count] = NULL;

    return (tokens);
}
