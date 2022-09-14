/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:21:51 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/14 17:14:39 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	childprcs(t_child child, char **argv, int *ends, char **envp)
{
	int	end;
	
	end = 0;
	if (child.num == 0)
		end = 1;
	if (child.num == 1)
		end = 0;
	dup2(child.fd, child.num);
	dup2(ends[end], end);
	close(ends[child.num]);
	close(child.fd);
	execve(child.path, child.cmd, envp);
	exit(EXIT_FAILURE);
}

void	pipex(char *argv[], char *envp[], t_child child1, t_child child2)
{
	int ends[2];
	int status;

	pipe(ends);
	child1.prcs = fork();
	//errorcheck
	if (child1.prcs == 0)
		childprcs(child1, argv, ends, envp);
	waitpid(child1.prcs, &status, 0);
	child2.prcs = fork();
	//errorcheck
	if (child2.prcs == 0)
		childprcs(child2, argv, ends, envp);
	close(ends[0]);
	close(ends[1]);
	waitpid(child1.prcs, &status, 0);
	waitpid(child2.prcs, &status, 0);
	//freeall(child1, child2);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_child child1;
	t_child child2;

	child1 = parse(argv[1], argv[2], envp, child1, 0);
	child2 = parse(argv[4], argv[3], envp, child2, 1);
	pipex(argv, envp, child1, child2);
	return(0);
}
