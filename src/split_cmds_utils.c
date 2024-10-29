/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:53:06 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/15 11:12:30 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*concat_strs(char *s1, char *s2)
{
	int		len1;
	int		len2;
	int		i;
	int		j;
	char	*result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	j = 0;
	result = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (s1[i] != '\0')
	{
		result[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

t_command	*allocate_node(void)
{
	t_command	*node;

	node = (t_command *)my_malloc(sizeof(t_command), 1);
	if (!node)
		return (my_malloc(0, 0), exit(10), NULL);
	node->cmd = NULL;
	node->redirection = NULL;
	node->is_ambiguous = -1;
	node->ambiguous_file = NULL;
	node->next = NULL;
	node->last_file = NULL;
	node->pipe[0] = -1;
	node->pipe[1] = -1;
	return (node);
}

int	ft_is_red(char *str)
{
	if (!ft_strcmp(str, ">") || !ft_strcmp(str, ">>") || !ft_strcmp(str, "<"))
		return (1);
	return (0);
}

void	printstrs(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!map)
		return ;
	while (map[i])
	{
		printf("|%s|\n", map[i]);
		i++;
	}
}
