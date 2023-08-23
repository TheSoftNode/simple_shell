#include "UShell.h"

/**
 * _strlen - returns the length of a string
 * @s: the string to check
 *
 * Return: integer length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (0);

	while (*s++)
		len++;

	return (len);
}

/**
 * _strcpy - copies a string from src to dest
 * @dest: the destination
 * @src: the source
 *
 * Returns: pointer to the destination
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i = 0;

	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	dest[i] = '\0';

	return (dest);
}

/**
 * _strchr - locates a character in a string
 * @s: the string to be searched
 * @c: the character to be located
 *
 * Return: if c is found - a pointer to the first occurence
 * if c is not found - NULL
 */
char *_strchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
			return (s + i);
	}

	return (NULL);
}

/**
 * _strcat - concantenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	int i = 0;
	int len = _strlen(dest);

	while (src[i])
		dest[len++] = src[i++];

	dest[len] = '\0';

	return (dest);
}

