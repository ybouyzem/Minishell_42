/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:26:37 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/14 15:51:52 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strslen(char **map)
{
	int	i;

	if (map == NULL)
		return (0);
	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	count_words_helper(char *old_cmd, int *i, int *len, char c)
{
	*len = *len + 1;
	*i = *i + 1;
	while (old_cmd[*i] && old_cmd[*i] != c)
		*i = *i + 1;
	*i = *i + 1;
}

int	ft_count_word(char *old_cmd)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	while (old_cmd[vars.i])
	{
		if (old_cmd[vars.i] == '"')
			count_words_helper(old_cmd, &vars.i, &vars.len, '"');
		else if (old_cmd[vars.i] == '\'')
			count_words_helper(old_cmd, &vars.i, &vars.len, '\'');
		else
		{
			vars.len++;
			while (old_cmd[vars.i] && old_cmd[vars.i] != '\''
				&& old_cmd[vars.i] != '"')
				vars.i++;
		}
	}
	return (vars.len);
}

void	expanding_split_helper(char *old_cmd, int *i, char c)
{
	*i = *i + 1;
	while (old_cmd[*i] && old_cmd[*i] != c)
		*i = *i + 1;
	*i = *i + 1;
}

char	**expanding_split(char *old_cmd)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	vars.res = ft_allocate(ft_count_word(old_cmd));
	while (old_cmd[vars.i])
	{
		vars.start = vars.i;
		if (old_cmd[vars.i] == '"')
			expanding_split_helper(old_cmd, &vars.i, '"');
		else if (old_cmd[vars.i] == '\'')
			expanding_split_helper(old_cmd, &vars.i, '\'');
		else
		{
			while (old_cmd[vars.i] && old_cmd[vars.i] != '\''
				&& old_cmd[vars.i] != '"')
				vars.i++;
		}
		vars.res[vars.index]
			= ft_substr(old_cmd, vars.start, vars.i - vars.start);
		vars.index++;
	}
	vars.res[vars.index] = 0;
	return (vars.res);
}
