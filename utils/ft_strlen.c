/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: marlou <marlou@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 14:26:09 by marlou        #+#    #+#                 */
/*   Updated: 2022/09/14 14:04:27 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
