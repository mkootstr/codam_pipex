typedef struct	s_child
{
	char *cmd;
	char *path;
}				t_child;

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
		close(ends[0]);
		dup2(ends[1], 1);
		child = parsecmd(args[2], envp, child);
		childprocess(envp, child);
		//	write(1, "child1 process\n", 15);
		return (0);
	}
	child2 = fork();
	if (child2 < 0)
		return (0);
	if (child2 == 0)
	{
		close(ends[1]);
		dup2(ends[0], 0);
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
	child.path = NULL;
	child.num = NULL;

	pipex(argv, envp, child);
	return(0);
}