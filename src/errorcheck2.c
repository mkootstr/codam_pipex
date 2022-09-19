/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errorcheck2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 20:44:25 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/19 21:19:13 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pfatal(const char *msg, int error)
{
	if (error != -1)
	{
		write(1, "Fatal: ", 7);
		if (msg != NULL)
			perror(msg);
	}
	error = -1;
	return (error);
}

int	ft_dup2(int fd1, int fd2)
{
	int	fd;

	fd = dup2(fd1, fd2);
	if (fd == -1)
		fatal("dup2 error");
	return (fd);
}

int	ft_close(int fd)
{
	int	rv;

	rv = close(fd);
	if (rv == -1)
		fatal("close error");
	return (rv);
}

int	cmdnotfound(char *cmd, int error)
{
	if (error != -1)
	{
		write(2, "Fatal: ", 7);
		ft_putstr_fd(cmd, 2);
		write(2, ": command not found\n", 20);
	}
	error = -1;
	return (error);
}
