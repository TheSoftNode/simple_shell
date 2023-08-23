#include "UShell.h"

/**
 * _strncat - concatenates two strings by
 * copying n number of bytes from
 * the source
 * @dest: a point to destination string 
 * @src: a pointer to source string
 * @n: number of bytes to copy
 *
 * Return: Pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t i = 0;
	size_t len = _strlen(dest);

	while (src[i] != '\0' && i < n)
	{
		dest[len + i] = src[i];
		i++;
	}

	dest[len + i] = '\0';

	return (dest);
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: string to be searched
 * @accept: the prefixed to be checked
 *
 * Return: the number of bytes in s which
 * consists only of bytes from accept
 */
int _strspn(char *s, char *accept)
{
	int bytes = 0;
	int i, j;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; accept[j]; j++)
		{
			if (s[i] == accept[j])
			{
				bytes++;
				break;
			}
			else if (accept[j + 1] == '\0')
				return (bytes);
		}
	}

	return (bytes);
}

/**
 * _strcmp - compares two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: positive byte if s1 > s2
 * 0 if s1 = s2
 * negative byte if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0;
	int diff;

	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
		{
			diff = s1[i] - s2[i];
			break;
		}
		diff = s1[i] - s2[i];

		i++;
	}

	return (diff);
}

/**
 * _strncmp - compares two strings
 * @s1: pointer to the first string
 * @s2: pointer to the second string
 * @n: the first n bytes of the strings to compare.
 *
 * Return: the difference in the strings
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] > s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] < s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);
	else
		return (-15);
}

