#include "UShell.h"

/**
 * handle_args - gets, calls, and runs the execution of a command
 * @exe_ret: the return value of the parent process' last executed command
 *
 * Return: if an end-of-file is read - END_OF_FILE (-2)
 *         if the input cannot be tokenized - -1
 *         O/w - The exit value of the last executed command
 */
int handle_args(int *exe_ret)
{
	int ret = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (ret);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

