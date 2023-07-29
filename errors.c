#include "shell.h"

/**
 * print_string - prints an input string.
 * @input_str: the string to be printed.
 *
 * Return: Nothing Much.
 */
void print_string(char *input_str)
{
    int index = 0;

    if (!input_str)
        return;
    while (input_str[index] != '\0')
    {
        print_character(input_str[index]);
        index++;
    }
}

/**
 * print_character - writes the character to stderr.
 * @ch: The character to print.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set acodinglly.
 */
int print_character(char ch)
{
    static int buffer_index = 0;
    static char buffer[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(2, buffer, buffer_index);
        buffer_index = 0;
    }
    if (ch != BUF_FLUSH)
        buffer[buffer_index++] = ch;
    return (1);
}

/**
 * write_character_to_fd - types the character to the given file descriptor
 * @ch: The character to print
 * @fd: The file descriptor to write onto.
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is displayed acodingly.
 */
int write_character_to_fd(char ch, int fd)
{
    static int buffer_index = 0;
    static char buffer[WRITE_BUF_SIZE];

    if (ch == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
    {
        write(fd, buffer, buffer_index);
        buffer_index = 0;
    }
    if (ch != BUF_FLUSH)
        buffer[buffer_index++] = ch;
    return (1);
}

/**
 * print_string_to_fd - prints an input string to the given file descriptor.
 * @input_str: the string to be printed.
 * @fd: the file descriptor to write onto.
 *
 * Retrun: number of characters puts.
 */
int print_string_to_fd(char *input_str, int fd)
{
    int index = 0;
    int count = 0;

    if (!input_str)
        return (0);
    while (input_str[index])
    {
        count += write_character_to_fd(input_str[index++], fd);
    }
    return (count);
}

