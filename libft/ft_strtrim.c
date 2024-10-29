/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:01:44 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 14:51:46 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

static size_t	ft_mysize(const char *start, const char *end)
{
	size_t	startlen;
	size_t	endlen;
	size_t	size;

	startlen = ft_strlen(start);
	endlen = ft_strlen(end);
	size = startlen - endlen;
	return (size);
}

static char	*allocate(char *s1, const char *end)
{
	char	*r;

	r = (char *)my_malloc(ft_mysize(s1, end) + 1, 1);
	if (r == NULL)
		return (my_malloc(0, 0), exit(10), NULL);
	return (r);
}

char	*ft_strtrim(char *s1, char const *set)
{
	const char	*end;
	char		*r;
	size_t		i;
	size_t		j;

	r = NULL;
	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = 0;
	end = s1 + ft_strlen(s1) - 1;
	while (s1[j] && ft_isspace(s1[j]))
		j++;
	while (end >= s1 && ft_isspace(*end))
		end--;
	end += 1;
	r = allocate(s1, end);
	while (j < ft_mysize(s1, end))
	{
		r[i] = s1[j];
		i++;
		j++;
	}
	r[i] = '\0';
	return (r);
}
