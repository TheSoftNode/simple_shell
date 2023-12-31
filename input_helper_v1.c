#include "UShell.h"

/**
 * exect_7 - just a wrapper function
 * @args: pointer to array of arguments
 * @front: a pointer to the first args
 * @exe_ret: a placeholder variable
 * @index: the for loop counter
 * @ret: the child process
 *
 * Return: ret
 */
int exect_7(char **args, char **front, int *exe_ret, int index, int ret)
{
	free(args[index]);
	args[index] = NULL;
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	if (*exe_ret == 0)
	{
		args = &args[++index];
		index = 0;
	}
	else
	{
		for (index++; args[index]; index++)
			free(args[index]);
		return (ret);
	}
	return (0);
}

/**
 * get_args - gets a command from standard input
 * @line: a buffer to store the command
 * @exe_ret: the return value of the last executed command
 *
 * Return: if an error occurs - NULL
 *         otherwise - a pointer to the stored command
 */
char *get_args(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}
/**
 * call_args - partitions operators from commands and calls them
 * @args: an array of arguments
 * @front: a double pointer to the beginning of args
 * @exe_ret: the return value of the parent process' last executed command
 *
 * Return: the return value of the last executed command
 */
int call_args(char **args, char **front, int *exe_ret)
{
	int ret, index;

	if (!args[0])
		return (*exe_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = replace_aliases(args);
			ret = run_args(args, front, exe_ret);
			if (*exe_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (ret);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			ret = exect_7(args, front, exe_ret, index, ret);
			return (ret);
		}
	}
	args = replace_aliases(args);
	ret = run_args(args, front, exe_ret);
	return (ret);
}

/**
 * run_args - calls the execution of a command
 * @args: an array of arguments
 * @front: a double pointer to the beginning of args
 * @exe_ret: the return value of the parent process' last executed command
 *
 * Return: the return value of the last executed command
 */
int run_args(char **args, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		ret = builtin(args + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(args, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (ret);
}

/**
 * check_args - checks if there are any leading ';', ';;', '&&', or '||'
 * @args: 2D pointer to tokenized commands and arguments
 *
 * Return: if a ';', '&&', or '||' is placed at an invalid position - 2
 *	   otherwise - 0
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nex = args[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}

