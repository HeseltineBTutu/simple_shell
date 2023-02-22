#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024
/**
 * _getline - reads an entire line froma file descriptor
 * @lineptr: pointer to a buffer for storing the line
 * @n: pointer to the size of the buffer
 * @stream: pointer to the input stream
 *
 * Return: the number of bytes read, or -1 on error or end of file
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
    static char buf[BUF_SIZE];
    static size_t buf_pos = 0;
    static ssize_t buf_size = 0;
    int i, eof = 0;
    ssize_t count = 0;
    int nl_pos = -1;
    char *new_lineptr;

    if (lineptr == NULL || n == NULL || stream == NULL) {
        return -1;
    }

    if (*lineptr == NULL || *n == 0) {
        *n = BUF_SIZE;
        *lineptr = malloc(*n);
        if (*lineptr == NULL) {
            return -1;
        }
    }

    while (!eof) {
        /*Check if there's a newline in the buffer*/
        for (i = buf_pos; i < buf_size; i++) {
            if (buf[i] == '\n') {
                nl_pos = i;
                break;
            }
        }

        if (nl_pos != -1) {
            /*Copy characters up to newline into lineptr*/
            if (count + nl_pos - buf_pos + 1 > *n) {
                /*Allocate a larger buffer if necessary*/
                *n = count + nl_pos - buf_pos + 1;
                new_lineptr = realloc(*lineptr, *n);
                if (new_lineptr == NULL) {
                    return -1;
                }
                *lineptr = new_lineptr;
            }
            memcpy(*lineptr + count, buf + buf_pos, nl_pos - buf_pos + 1);
            count += nl_pos - buf_pos + 1;
            buf_pos = nl_pos + 1;
            break;
        } else {
            /* Copy all remaining characters into lineptr*/
            if (count + buf_size - buf_pos > *n) {
                /*Allocate a larger buffer if necessary*/
                *n = count + buf_size - buf_pos;
                new_lineptr = realloc(*lineptr, *n);
                if (new_lineptr == NULL) {
                    return -1;
                }
                *lineptr = new_lineptr;
            }
            memcpy(*lineptr + count, buf + buf_pos, buf_size - buf_pos);
            count += buf_size - buf_pos;
            buf_pos = 0;
        }

        /*Fill buffer with more data*/
        buf_size = read(fileno(stream), buf, BUF_SIZE);
        if (buf_size <= 0) {
            eof = 1;
            break;
        }
    }

    if (count == 0 && eof) {
        /*Nothing was read and EOF was encountered*/
        return -1;
    }

    (*lineptr)[count] = '\0';
    return count;
}
