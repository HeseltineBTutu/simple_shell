#include "main.h"

/**
 * getline_custom - Custom implementation of the getline function
 * @lineptr: Pointer to a pointer to the buffer where the line will be stored
 * @n: Pointer to the size of the buffer
 * @stream: File stream from which to read (could be stdin or a file)
 *
 * This function reads a line from the given stream and dynamically allocates
 *  * memory for the line. The buffer is resized as needed to accommodate longer lines.
 *  The function terminates the line with a null character ('\0').
 *
 *  Return: The number of characters read, including the newline character.
 *          Returns -1 in case of errors (memory allocation or reallocation failures).
 */
ssize_t getline_custom(char **lineptr, size_t *n, FILE *stream)
{
	int c;
	size_t i = 0;
	char buffer[BUFFER_SIZE];
	size_t newSize;

	/* Check if *lineptr is NULL or *n is 0 */
	if (*lineptr == NULL || *n == 0)
	{
		/* Set *n to INITIAL_BUFFER_SIZE */
		*n = INITIAL_BUFFER_SIZE;
		*lineptr = (char *)malloc(*n); /* Allocate memory for *lineptr using malloc */
		if (*lineptr == NULL)
			return (-1);
	}

	while ((c = fgetc(stream)) != EOF && c != '\n')
	{
		if (i < BUFFER_SIZE - 1)
		{
			/* Append characters to the buffer */
			buffer[i++] = (char)c;
		}
		else
		{
			
			/* Resize the line buffer if the buffer is full */
			newSize = *n + i + 1;
			*lineptr = realloc(*lineptr, newSize);

			if (*lineptr == NULL)
			{
				return (-1);
			}

			memcpy(*lineptr + *n - BUFFER_SIZE, buffer, i);
			*n = newSize;
			i = 0;
		}
	}

	memcpy(*lineptr + *n - BUFFER_SIZE, buffer, i);
	(*lineptr)[*n - BUFFER_SIZE + i] = '\0';

	if (i == 0 && c == EOF)
	{
		return (-1);
	}
	return (*n - BUFFER_SIZE + i);
}

