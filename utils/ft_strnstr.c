/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: marlou <marlou@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 17:09:02 by marlou        #+#    #+#                 */
/*   Updated: 2022/09/14 14:04:25 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
