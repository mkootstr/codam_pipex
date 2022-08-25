#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

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

void	ft_r1(char *string)
{
	char temp;
	int i;

	i = 0;
	while (string[i] != '\0' && string[i + 1] != '\0')
		i++;
	temp = string[i];
	i--;
	while (i >= 0)
	{
		string[i + 1] = string[i];
		i--;
	}
	string[0] = temp;
}

char **parse(char *argv[], int argc)
{
	char **args;

	args = ft_split(argv[1], ' ');
	if (!args)
		return (NULL);
	args[0] = ft_append(args[0], "/", 1);
	ft_r1(args[0]);
	return(args);
}

char			*ft_strdup(const char *src)
{
	char	*dest;
	size_t	i;
	size_t	srclen;

	i = 0;
	if (!src)
		return(NULL);
	srclen = ft_strlen(src);
	dest = (malloc((srclen + 1) * sizeof(char)));
	if (dest)
	{
		while (src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (dest);
}

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

char *specpath(char *path, char *command)
{
	char **split;
	int	i;

	split = ft_split(path, ':');
	i = 0;
	if (split)
	{
		while(split[i])
		{
			split[i] = ft_append(split[i], command, ft_strlen(command));
			i++;
		}
		i = 0;
		while(open(split[i], O_RDONLY) == -1)
			i++;
		return (split[i]);
	}
	free(path);
	return (NULL);
}

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

int main(int argc, char *argv[], char *envp[])
{
	char **args;
	
	args = parse(argv, argc);
	char *path = findpath(envp, args[0]);
	printf("%s\n", path);
	execve(path, args, envp);
	return(0);
}
