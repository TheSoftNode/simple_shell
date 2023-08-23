#include "UShell.h"

/**
 * tok_len - locates the first token(del) in string
 * @s: the string to be searched
 * @del: the delimiter character
 *
 * Return: the delimiter index marking the end of
 *         the intitial token pointed to be str.
 */
int tok_len(char *s, char *del)
{
	int i = 0, len = 0;

	while (s[i] && s[i] != *del)
	{
		i++;
		len++;
	}

	return (len);
}

/**
 * tok_count - counts the number of delimited
 *                words in a string
 * @str: the string to be searched
 * @del: the delimiter character
 *
 * Return: the number of words contained within str
 */
int tok_count(char *s, char *del)
{
	int i = 0;
	int count = 0;
	int len = _strlen(s);

	while (i < len)
	{
		if (s[i] != *del)
		{
			count++;
			i += tok_len(s + i, del);
		}
		i++;
	}

	return (count);
}

/**
 * _strtok - tokenizes a string
 * @line: the string
 * @del: the delimiter character to tokenize the string by
 *
 * Return: a pointer to an array containing the tokenized words
 */
char **_strtok(char *line, char *del)
{
	char **ptr;
	int i = 0;
	int t, l, tokens, letters;

	tokens = tok_count(line, del);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[i] == *del)
			i++;

		letters = tok_len(line + i, del);

		ptr[t] = malloc(letters + 1);
		if (!ptr[t])
		{
			for (i -= 1; i >= 0; i--)
				free(ptr[i]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[i];
			i++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

