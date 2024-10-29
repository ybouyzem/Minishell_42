/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:25:03 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/17 12:17:58 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

int	split_count_words(const char *s)
{
	int	i;
	int	nbr;

	if (!s)
		return (0);
	i = 0;
	nbr = 0;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] != '\0')
			nbr++;
		while (s[i] && !ft_isspace(s[i]))
			i++;
	}
	return (nbr);
}

static char	*ft_mystrdup( const char *s, char charset)
{
	char	*r;
	int		i;
	int		lw;

	charset = ' ';
	i = 0;
	lw = 0;
	while (s[lw] && !ft_isspace(s[lw]))
		lw++;
	r = (char *)my_malloc(lw + 1, 1);
	if (r == NULL)
		return (my_malloc(0, 0), exit(10), NULL);
	while (i < lw)
	{
		r[i] = s[i];
		i++;
	}
	r[i] = '\0';
	return (r);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		index;
	char	*tmp;

	if (!s)
		return (NULL);
	index = 0;
	result = ft_allocate(split_count_words(s));
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (*s != '\0')
		{
			tmp = ft_mystrdup(s, c);
			if (!tmp)
				return (NULL);
			else
				result[index++] = tmp;
		}
		while (*s && !ft_isspace(*s))
			s++;
	}
	result[index] = 0;
	return (result);
}
