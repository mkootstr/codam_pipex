/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_append.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 13:01:25 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/14 17:39:55 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

char	*ft_append(char *allocstr1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!allocstr1 || !s2)
		return (NULL);
	i = ft_strlen(allocstr1);
	j = ft_strlen(s2);
	s3 = ft_calloc((i + j + 1), sizeof(char));
	i = 0;
	j = 0;
	while (allocstr1[i] != '\0' && s3)
	{
		s3[i] = allocstr1[i];
		i++;
	}
	while (s2[j] != '\0' && s3)
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	free(allocstr1);
	return (s3);
}
