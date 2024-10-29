/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 17:51:49 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/15 11:11:35 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	ls1;
	size_t	ls2;
	char	*r;
	size_t	len;
	size_t	tmp;

	if (!s1)
		return (my_strdup(s2));
	else if (!s2)
		return (my_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	len = ls1 + ls2 + 1;
	r = (char *)my_malloc(len, 1);
	if (r == NULL)
		return (my_malloc(0, 0), exit(10), NULL);
	tmp = ft_strlcpy(r, s1, ls1 + 1);
	tmp = ft_strlcat(r, s2, len);
	return (r);
}
