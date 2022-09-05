#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_child
{
	char **cmd;
	char *path;
	pid_t prcs;
	int	fd;
	int num;
}				t_child;

int	main(int argc, char *argv[], char *envp[])
{
	int	fdin;
	int	fdout;

	fdin = open(argv[1], O_RDONLY);
	fdout = open(argv[4], O_CREAT, O_RDWR, O_TRUNC);
	//error fd
	pipex(argv, envp);
	return(0);
}

void	pipex(int fdin, int fdout, char *argv[], char *envp[])
{
	t_child child1;
	t_child child2;
	int ends[2];
	int status;

	child1 = parse(argv[1], argv[2], envp, child1, 0);
	child2 = parse(argv[4], argv[3], envp, child2, 1);
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
	freeall(child1, child2);
	return ;
}

t_child	parse(char *file, char *command, char **envp, t_child child, int num)
{
	child.cmd = ft_split(command, ' ');
	child.path = findpath(child.cmd[0], envp);
	child.num = (int) malloc(1 * sizeof(int));
	child.num = num;
	if (child.num == 0)
		child.fd = open(file, O_RDONLY);
	else if (child.num == 1)
		child.fd = open(file, O_CREAT, O_RDWR, O_TRUNC); 
	return (child);
}

char	*findpath(char *cmd, char *envp[])
{

}

void	childprcs(t_child child, char **argv, int *ends, char **envp)
{
	int	end;

	end = 0;
	if (child.num == 1)
		end = 0;
	if (child.num == 0)
		end = 1;
	dup2(child.fd, child.num);
	dup2(ends[end], end);
	close(ends[child.num]);
	close(child.fd);
	execve(child.path, child.cmd, envp);
	exit(EXIT_FAILURE);
}

int	freeall(t_child child1, t_child child2)
{

}