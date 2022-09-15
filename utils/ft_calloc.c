/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 15:13:43 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/15 08:44:49 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	char	*ptr;
	size_t	a;
	size_t	i;

	a = nitems * size;
	i = 0;
	ptr = malloc(a);
	if (ptr != NULL)
	{
		while (i < a)
		{
			ptr[i] = 0;
			i++;
		}
	}
	return (ptr);
}
