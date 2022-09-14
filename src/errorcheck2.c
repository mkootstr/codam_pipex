/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errorcheck2.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 20:44:25 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/14 21:14:46 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
