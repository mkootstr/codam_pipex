/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:21:51 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/19 19:52:43 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childprcs(t_child child, int *ends, char **envp)
{
	int	end;

	end = 0;
	if (child.num == 0)
		end = 1;
	if (child.num == 1)
		end = 0;
	ft_dup2(child.fd, child.num);
	ft_dup2(ends[end], end);
	ft_close(ends[child.num]);
	ft_close(child.fd);
	execve(child.path, child.cmd, envp);
	fatal(child.cmd[0]);
	exit(EXIT_FAILURE);
}

void	pipex(char *envp[], t_child child1, t_child child2)
{
	int	ends[2];
	int	status;

	ft_pipe(ends);
	child1.prcs = ft_fork();
	if (child1.prcs == 0)
		childprcs(child1, ends, envp);
	ft_waitpid(child1.prcs, &status, 0);
	child2.prcs = ft_fork();
	if (child2.prcs == 0)
		childprcs(child2, ends, envp);
	ft_close(ends[0]);
	ft_close(ends[1]);
	ft_waitpid(child2.prcs, &status, 0);
	freechild(child1);
	freechild(child2);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_child	child1;
	t_child	child2;

	if (argc != 5)
	{
		write(2, "Fatal: Wrong number of arguments\n", 33);
		exit(1);
	}
	child1.num = 0;
	child2.num = 1;
	child1 = parse(argv[1], argv[2], envp, child1);
	child2 = parse(argv[4], argv[3], envp, child2);
	if (child1.error == -1 || child2.error == -1)
		exit(1);
	pipex(envp, child1, child2);
	ft_close(child1.fd);
	ft_close(child2.fd);
	return (0);
}
