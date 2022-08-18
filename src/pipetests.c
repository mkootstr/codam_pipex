/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipetests.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 18:12:43 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/08/18 20:18:55 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct	s_child
{
	char *cmd;
	char *flags;
	char *path;
}				t_child;

int childprocess(char *environment, t_child child)
{

}

char	*findflags(char *args)
{
	
}

char	*findcmd(char *args)
{

}

t_child parsecmd(char *args, char *environment, t_child child)
{	
	child.cmd = findcmd(args); //command en flags moeten samen nog
	child.flags = findflags(args);
	child.path = findpath(environment, child.cmd);
	return (child);
}

int	pipex(char *args[], char *envp[], t_child child)
{
	int	ends[2];
	int status;
	pid_t	child1;
	pid_t	child2;

	pipe(ends);
	child1 = fork();
	if (child1 < 0)
		return (0);
	if (child1 == 0)
	{
		child = parsecmd(args[2], envp, child);
		childprocess(envp, child);
		//write(1, "child1 process\n", 15);
		return (0);
	}
	child2 = fork();
	if (child2 < 0)
		return (0);
	if (child2 == 0)
	{
		child = parsecmd(args[3], envp, child);
		childprocess(envp, child);
		//write(1, "child2 process\n", 15);
		return (0);
	}
	close(ends[0]);
	close(ends[1]);
	waitpid(child1, status, NULL);
	waitpid(child2, status, NULL);
	return (0);
}

int main(int argc, char *argv[], char *envp[])
{
	t_child child;
	
	child.cmd = NULL;
	child.flags = NULL;
	child.path = NULL;

	pipex(argv, envp, child);

}