/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errorcheck2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 20:44:25 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/10/02 14:54:35 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(t_child child)
{
	int	error;

	error = 1;
	if (child.error == 127)
		error = 127;
	if (child.num == 1)
	{
		if (child.error != 0)
			exit(error);
	}
	else if (child.num == 0)
	{
		if (child.error != 0)
			exit(0);
	}
}

int	pfatal(const char *msg, int error)
{
	if (error != -1)
	{
		write(1, "Pipex: ", 7);
		if (msg != NULL)
			perror(msg);
	}
	error = -1;
	return (error);
}

int	ft_dup2(int fd1, int fd2)
{
	int	fd;

	fd = 0;
	if (fd1 != -1 && fd2 != -1)
	{
		fd = dup2(fd1, fd2);
		if (fd == -1)
			fatal("dup2 error");
	}
	return (fd);
}

int	ft_close(int fd)
{
	int	rv;

	rv = 0;
	if (fd != -1)
	{
		rv = close(fd);
		if (rv == -1)
			fatal("close error");
	}
	return (rv);
}

int	cmdnotfound(char *cmd, int error)
{
	if (error == 0)
	{
		write(2, "Pipex: ", 7);
		ft_putstr_fd(cmd, 2);
		write(2, ": command not found\n", 20);
	}
	error = 127;
	return (error);
}
