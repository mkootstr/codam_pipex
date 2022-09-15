/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 15:15:14 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/15 09:00:56 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "../utils/utils.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>

typedef struct s_child
{
	char	**cmd;
	char	*path;
	pid_t	prcs;
	int		fd;
	int		num;
}				t_child;

void	pipex(char *envp[], t_child child1, t_child child2);
void	childprcs(t_child child, int *ends, char **envp);
t_child	parse(char *file, char *command, char **envp, t_child child);
char	*findpath(char *cmd, char *envp[]);
char	*specpath(char *env, char *cmd);
char	*checkaccess(char **splitpath, char *cmd);
void	freesplitpath(char **splitpath);
void	freechild(t_child child);
pid_t	ft_waitpid(pid_t pid, int *status, int option);
void	ft_pipe(int *p);
pid_t	ft_fork(void);
void	fatal(const char *msg)
		__attribute__((noreturn));
int		ft_close(int fd);
int		ft_dup2(int fd1, int fd2);

#endif