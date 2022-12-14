/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mkootstr <mkootstr@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/09/14 14:05:11 by mkootstr      #+#    #+#                 */
/*   Updated: 2022/09/19 19:22:57 by mkootstr      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <unistd.h>
# include <stdlib.h>

size_t	ft_strlen(const char *str);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_append(char *allocstr1, char *s2);
char	*ft_strdup(const char *src);
void	*ft_calloc(size_t nitems, size_t size);
void	ft_putstr_fd(char *s, int fd);

#endif