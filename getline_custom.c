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
	static char buffer[INITIAL_BUFFER_SIZE];
	static size_t buf_index = 0;
	static size_t buf_size = 0;

	int c;
	size_t i = 0;
	char *temp;
	
	if (stream == NULL || feof(stream))
	{
		if (i == 0)
		{
			return (0);
		}
		return (-1);
	}

	if (*lineptr == NULL || *n == 0)
	{
		*n = INITIAL_BUFFER_SIZE;
		*lineptr = (char *)malloc(*n * sizeof(char));
		if (*lineptr == NULL)
			return (-1);
	}

	while (1)
	{
		if (buf_index >= buf_size || buf_size == 0)
		{
			buf_size = read(fileno(stream), buffer, INITIAL_BUFFER_SIZE);
			buf_index = 0;

			if (buf_size <= 0)
			{
				break;
			}
		}
		c = buffer[buf_index++];
	        (*lineptr)[i++] = (char)c;
		if (i + 1 >= *n)
		{
			*n *= 2;
			temp = realloc(*lineptr, *n * sizeof(char));

		if (temp == NULL)
		{
			return (-1);
		}
		*lineptr = temp;
		}
		if (c == '\n')
		{
			break;
		}
	}

	(*lineptr)[i] = '\0';

	return (i);
}
