/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 10:55:09 by mkootstr      #+#    #+#                 */
/*   Updated: 2021/02/02 16:05:31 by marlou        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

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
