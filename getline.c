#include "main.h"

/**
 * allocate_buffer - allocate memory for the buffer
 * @size: size of the buffer
 *
 * Return: pointer to allocated buffer, or NULL on failure
 */
char *allocate_buffer(size_t size)
{
	char *buffer = malloc(size);
	if (!buffer)
		return NULL;
	return buffer;
}

/**
 * read_char - read a character from the input stream
 * @stream: input stream to read from
 * @c: pointer to variable to store the read character
 *
 * Return: 1 if a character was read successfully, 0 otherwise
 */
int read_char(FILE *stream, char *c)
{
	int n;
	static int end_of_file = 0;
	if (end_of_file)
		return 0;
	n = fread(c, 1, 1, stream);
	if (n == 0 && !feof(stream))
	{
		end_of_file = 1;
		return 0;
	}
	return 1;
}

/**
 * append_char - append a character to the buffer
 * @buffer: buffer to append to
 * @size: size of the buffer
 * @pos: current position in the buffer
 * @c: character to append
 *
 * Return: 1 on success, 0 on failure
 */
int append_char(char **buffer, size_t *size, size_t pos, char c)
{
	if (pos >= *size)
	{
		size_t new_size = *size * 2;
		char *new_buffer = allocate_buffer(new_size);
		if (!new_buffer)
			return 0;
		strncpy(new_buffer, *buffer, pos);
		free(*buffer);
		*buffer = new_buffer;
		*size = new_size;
	}
	(*buffer)[pos] = c;
	return 1;
}

/**
 * get_line - read a line of input from a stream
 * @lineptr: pointer to a buffer to store the input
 * @n: size of the buffer
 * @stream: input stream to read from
 *
 * Return: number of characters read, or -1 on failure
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	static char *buffer = NULL;
	static size_t buffer_size = 0;
	size_t pos = 0;
	char c;
	if (!buffer)
	{
		buffer_size = BUFSIZE;
		buffer = allocate_buffer(buffer_size);
		if (!buffer)
			return -1;
	}
	while (read_char(stream, &c))
	{
		if (c == '\n')
			break;
		if (!append_char(&buffer, &buffer_size, pos, c))
			return -1;
		pos++;
	}
	if (!append_char(&buffer, &buffer_size, pos, '\0'))
		return -1;
	if (*lineptr)
		free(*lineptr);
	*lineptr = buffer;
	if (*n < buffer_size)
		*n = buffer_size;
	buffer = NULL;
	buffer_size = 0;
	return pos;
}

