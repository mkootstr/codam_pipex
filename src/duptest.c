//typedef struct	s_child
//{
//	char *cmd;
//	char *path;
//	int   num;
//}				t_child;

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>


//struct nog in prototype van deze
void	pipex(char *args[], char *envp[])
{
	int	ends[2];
	int status;
	pid_t	child1;
	pid_t	child2;
	int		fdin;
	int		fdout;

	pipe(ends);
	child1 = fork();
	//if (child1 < 0)
	//	return (0);
	if (child1 == 0)
	{
		fdin = open("infile.txt", O_RDWR);
		
		char *args1[]= {"grep", "wow", NULL};
	//	child = parsecmd(args[2], envp, child);
	//	childprocess(envp, child);
		write(1, "child1 process\n", 15);
		dup2(fdin, 0);
		dup2(ends[1], 1);
		close(ends[0]);
		close(fdin);
		execve("/usr/bin/grep", args1, envp);
		exit(EXIT_FAILURE);
	}
	waitpid(child1, &status, 0);
	child2 = fork();
	//if (child2 < 0)
	//	return (0);
	if (child2 == 0)
	{
		fdout = open("outfile.txt", O_RDWR);
		char *args2[]= {"wc", "-l", NULL};
//		child = parsecmd(args[3], envp, child);
	//	childprocess(envp, child);
		write(1, "child2 process\n", 15);
		dup2(fdout, 1);
		dup2(ends[0], 0);
		close(ends[1]);
		close(fdout);
		execve("/usr/bin/wc", args2, envp);
		exit(EXIT_FAILURE);
	}
	close(ends[0]);
	close(ends[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
}

int main(int argc, char *argv[], char *envp[])
{
	//t_child child;
	
	//child.cmd = NULL;
	//child.path = NULL;
	//child.num = 0;

	pipex(argv, envp);
	return(0);
}