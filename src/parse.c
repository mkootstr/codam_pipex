/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:16:46 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/26 18:47:00 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

t_child	checkaccess(char **splitpath, char *cmd, t_child child)
{
	ssize_t	fd;
	int		i;

	fd = -1;
	i = 0;
	while (fd < 0 && splitpath[i])
	{
		fd = open(splitpath[i], O_RDONLY);
		i++;
	}
	if (fd >= 0)
	{
		child.path = ft_strdup(splitpath[i - 1]);
		ft_close(fd);
	}
	else if (fd < 0)
		child.error = cmdnotfound(cmd, child.error);
	return (child);
}

t_child	specpath(char *env, char *cmd, t_child child)
{
	char	**splitpath;
	int		i;

	splitpath = ft_split(env, ':');
	i = 0;
	if (splitpath)
	{
		while (splitpath[i] != NULL)
		{
			splitpath[i] = ft_append(splitpath[i], "/");
			splitpath[i] = ft_append(splitpath[i], cmd);
			i++;
		}
		child = checkaccess(splitpath, cmd, child);
		freesplitpath(splitpath);
	}
	return (child);
}

t_child	findpath(char *cmd, char *envp[], t_child child)
{
	int		i;

	i = 0;
	child.path = NULL;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH", 6) == NULL)
		i++;
	if (envp[i] != NULL)
		child = specpath(envp[i], cmd, child);
	return (child);
}

t_child	parse(char *file, char *command, char **envp, t_child child)
{
	child.path = NULL;
	child.error = 0;
	if (child.num == 0)
		child.fd = open(file, O_RDWR);
	else if (child.num == 1)
		child.fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (child.fd < 0)
		child.error = pfatal(file, child.error);
	child.cmd = ft_split(command, ' ');
	if (child.cmd != NULL)
		child = findpath(child.cmd[0], envp, child);
	return (child);
}
