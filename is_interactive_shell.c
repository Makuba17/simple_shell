#include "shell.h"

/**
 * is_interactive_shell - this confirms if shell is in interactive mode.
 * @info: Pointer to a struct containing shell info.
 *
 * Return: 1 if the shell is in interactive mode, 0 otherwise.
 */
int is_interactive_shell(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_character_delim - Confirms if a character is a delimiter.
 * @c: The character to confirm.
 * @delim: The delim string.
 *
 * Return: 1 if the character is a delim, 0 if false.
 */
int is_character_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim == c)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * is_character_alphabet-confirms if a character is an alphabetic character.
 * @c: The character to confirm.
 *
 * Return: 1 if c is alphabetic, 0 otherwise.
 */
int is_character_alphabet(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * str_to_int - changes a string to an integer.
 * @s: The string to be converted.
 *
 * Return: 0 if no numbers in the string, converted number otherwise.
 */
int str_to_int(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-'
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
