/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:08:19 by alamini           #+#    #+#             */
/*   Updated: 2024/10/16 17:18:03 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

char	*my_strdup(const char *s1) // garbage collector strdup
{
	char	*ptr;
	int		size;
	int		i;

	size = ex_strlen(s1);
	ptr = my_malloc((sizeof(char) * (size + 1)), 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	*ex_strjoin(char *s1, char *s2) // normal strjoin with free s1
{
	char	*res;
	int		length;
	int		i;
	int		j;

	if (!s1)
		return (ex_strdup(s2));
	if (!s2)
		return (s1);
	length = ex_strlen(s1) + ex_strlen(s2);
	res = (char *)malloc(sizeof(char) * length + 1);
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (free(s1), res);
}

char	*my_strjoin(char *s1, char *s2) // garbage collector join
{
	char	*res;
	int		length;
	int		i;
	int		j;

	if (!s1)
		return (my_strdup(s2));
	if (!s2)
		return (s1);
	length = ex_strlen(s1) + ex_strlen(s2);
	res = (char *)my_malloc(sizeof(char) * length + 1, 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*special_join(char *s1, char *s2) // a join without free
{
	char	*res;
	int		length;
	int		i;
	int		j;

	if (!s1)
		return (ex_strdup(s2));
	if (!s2)
		return (s1);
	length = ex_strlen(s1) + ex_strlen(s2);
	res = (char *)malloc(sizeof(char) * length + 1);
	if (!res)
		return (0);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
