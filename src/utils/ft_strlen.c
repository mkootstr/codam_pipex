/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marlou <marlou@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 14:26:09 by marlou        #+#    #+#                 */
/*   Updated: 2022/07/31 16:54:04 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return(0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
