/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:15:14 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/14 14:45:14 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../utils/utils.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_child
{
	char **cmd;
	char *path;
	pid_t prcs;
	int	fd;
	int num;
}				t_child;

void	pipex(char *argv[], char *envp[], t_child child1, t_child child2);
void	childprcs(t_child child, char **argv, int *ends, char **envp);
t_child	parse(char *file, char *command, char **envp, t_child child, int num);
char	*findpath(char *cmd, char *envp[]);
char	*specpath(char *env, char *cmd);
char	*checkaccess(char **splitpath);
void	freesplitpath(char **splitpath);
void	freeall(t_child child1, t_child child2);

#endif