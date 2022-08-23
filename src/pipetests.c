/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipetests.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/08/18 18:12:43 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/08/23 15:48:39 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct	s_child
{
	int num;
	char *cmd;
	char *path;
}				t_child;
//=================================================================================================================
size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return(0);
	while (str[i] != '\0')
		i++;
	return (i);
}
//================================================================================================================
static char		**ft_fill(char **split, char const *s, char c)
{
	size_t len;
	size_t i;
	size_t n;

	len = 0;
	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i] != '\0' && s[i] != c)
		{
			split[n][len] = s[i];
			i++;
			len++;
		}
		split[n][len] = '\0';
		n++;
		len = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (split);
}

static char		**ft_free(char **split, size_t n)
{
	while (n > 1)
	{
		free(split[n - 2]);
		n--;
	}
	free(split);
	return (NULL);
}

static char		**ft_wrdlen(char **split, char const *s, char c)
{
	size_t wrdlen;
	size_t i;
	size_t n;

	n = 0;
	i = 0;
	wrdlen = 0;
	while (s[i] != '\0' && split != NULL)
	{
		wrdlen = 0;
		while (s[i] == c && s[i] != '\0')
			i++;
		while (s[i + wrdlen] != c && s[i + wrdlen] != '\0')
			wrdlen++;
		if (wrdlen != 0)
		{
			split[n] = (char *)malloc((wrdlen + 1) * sizeof(char));
			n++;
		}
		if (!split[n - 1])
			split = ft_free(split, n);
		i = i + wrdlen;
	}
	return (split);
}

static size_t	ft_wrdcnt(char const *s, char c)
{
	size_t	i;
	size_t	wrdcnt;

	i = 0;
	wrdcnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
		{
			wrdcnt++;
		}
		i++;
	}
	return (wrdcnt);
}

char			**ft_split(char const *s, char c)
{
	char	**split;
	size_t	wrdcnt;

	if (!s)
		return (NULL);
	wrdcnt = ft_wrdcnt(s, c);
	split = (char **)malloc((wrdcnt + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	if (split && wrdcnt != 0)
		split = ft_wrdlen(split, s, c);
	if (split && wrdcnt != 0)
		split = ft_fill(split, s, c);
	if (split)
		split[wrdcnt] = NULL;
	else
		split = NULL;
	return (split);
}
//=================================================================================================================
char 	*ft_append(char *line, char *buf, size_t l)
{
	char	*new_line;
	size_t	line_size;

	line_size = ft_strlen(line);
	new_line = malloc((line_size + 1 + l) * sizeof(char));
	if (!new_line)
	{
		free(line);
		return (NULL);
	}
	new_line[line_size + l] = '\0';
	while (l--)
		new_line[line_size + l] = buf[l];
	while (line_size--)
		new_line[line_size] = (line)[line_size];
	free(line);
	return (new_line);
}
//=================================================================================================================
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len > 0)
	{
		j = 0;
		while (haystack[i] == needle[j] && j < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + (i - j));
			i++;
			j++;
		}
		i = i - j;
		i++;
		len--;
	}
	return (NULL);
}
//=================================================================================================================
char *specpath(char *path, char *command)
{
	char **split;
	int	i;
	int check;

	split = ft_split(path, ':');
	i = 0;
	check = -1;
	if (split)
	{
		while(split[i])
		{
			split[i] = ft_append(split[i], command, ft_strlen(command));
			i++;
		}
		i = -1;
		while( check == -1)
		{
			i++;
			check = open(split[i], O_RDONLY);
		}
		close(check);
		return (split[i]);
	}
	free(path);
	return (NULL);
}
//=================================================================================================================
char *findpath(char **environment, char *command)
{
	int i;
	char *path;

	i = 0;
	path = NULL;
	while(path == NULL && environment[i])
	{
		if (ft_strnstr(environment[i], "PATH=", 6) != NULL)
			path = ft_strdup(ft_strnstr(environment[i], "PATH=", 6));
		i++;
	}
	path = specpath(path, command);
	return (path);
}
//=================================================================================================================
int childprocess(char *environment, t_child child)
{

}
//=================================================================================================================
char	**findcmd(char *args)
{

}
//=================================================================================================================
t_child parsecmd(char *args, char *environment, t_child child)
{	
	child.cmd = findcmd(args);
	child.path = findpath(environment, child.cmd);
	return (child);
}
//=================================================================================================================
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
//=================================================================================================================
int main(int argc, char *argv[], char *envp[])
{
	t_child child;
	
	child.cmd = NULL;
	child.path = NULL;
	child.num = NULL;

	pipex(argv, envp, child);
	return(0);
}