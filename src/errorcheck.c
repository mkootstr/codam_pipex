/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errorcheck.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:23:31 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/15 09:01:24 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fatal(const char *msg)
{
	write(1, "Fatal: ", 7);
	if (msg != NULL)
		perror(msg);
	exit(1);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		fatal("fork error");
	return (pid);
}

void	ft_pipe(int *p)
{
	if (pipe(p) == -1)
		fatal("pipe error");
}

pid_t	ft_waitpid(pid_t pid, int *status, int option)
{
	pid_t	rv;

	rv = waitpid(pid, status, option);
	if (rv == -1)
		fatal("waitpid error");
	return (rv);
}

void	freechild(t_child child)
{
	int	i;

	i = 0;
	if (child.path)
		free(child.path);
	if (child.cmd)
	{
		while (child.cmd[i] != NULL)
		{
			free(child.cmd[i]);
			i++;
		}
		free(child.cmd);
	}
}
