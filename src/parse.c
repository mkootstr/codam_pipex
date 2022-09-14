/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:16:46 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/14 21:18:31 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

void	freesplitpath(char **splitpath)
{
	int	i;

	i = 0;
	if (splitpath)
	{
		while (splitpath[i] != NULL)
		{
			free(splitpath[i]);
			i++;
		}
		free(splitpath);
	}
}

char	*checkaccess(char **splitpath, char *cmd)
{
	char	*path;
	ssize_t	fd;
	int		i;

	fd = -1;
	i = 0;
	path = NULL;
	while (fd < 0 && splitpath[i])
	{
		fd = open(splitpath[i], O_RDONLY);
		i++;
	}
	if (fd >= 0)
	{
		path = ft_strdup(splitpath[i - 1]);
		close(fd);
	}
	else if (fd < 0)
	{
		perror(cmd);
		exit(EXIT_FAILURE);
	}
	return (path);
}

char	*specpath(char *env, char *cmd)
{
	char	**splitpath;
	char	*path;
	int		i;

	splitpath = ft_split(env, ':');
	i = 0;
	path = NULL;
	if (splitpath)
	{
		while (splitpath[i] != NULL)
		{
			splitpath[i] = ft_append(splitpath[i], "/");
			splitpath[i] = ft_append(splitpath[i], cmd);
			i++;
		}
		path = checkaccess(splitpath, cmd);
		freesplitpath(splitpath);
	}
	return (path);
}

char	*findpath(char *cmd, char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (ft_strnstr(envp[i], "PATH", 6) == NULL && envp[i] != NULL)
		i++;
	if (envp[i] != NULL)
		path = specpath(envp[i], cmd);
	return (path);
}

t_child	parse(char *file, char *command, char **envp, t_child child)
{
	if (child.num == 0)
		child.fd = open(file, O_RDWR);
	else if (child.num == 1)
		child.fd = open(file, O_RDWR | O_CREAT);
	if (child.fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	child.cmd = ft_split(command, ' ');
	if (child.cmd != NULL)
		child.path = findpath(child.cmd[0], envp);
	return (child);
}
