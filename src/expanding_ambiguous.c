/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_ambiguous.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 07:33:57 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 13:47:35 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	check_will_splited_helper_ambg1(t_env *envs, t_vars vars, char **cmd, int i)
{
	while (cmd[i][vars.j])
	{
		if (cmd[i][vars.j] == '$' && cmd[i][vars.j + 1])
		{
			skip_dollars(cmd, i, &vars.j, &vars.nbr);
			if (vars.nbr % 2 != 0)
			{
				vars.start = vars.j;
				while (cmd[i][vars.j] && ft_isalpha(cmd[i][vars.j])
					&& cmd[i][vars.j] != '"')
					vars.j++;
				vars.key = ft_substr(cmd[i],
						vars.start - 1, vars.j - vars.start + 1);
				vars.value = double_quotes_p(envs, vars.key, NULL, 0);
				if (split_count_words(vars.value) > 1)
					vars.check = 1;
			}
			else
				vars.check = 0;
		}
		else
			vars.j++;
	}
	return (vars.check);
}

int	check_will_splited_ambg(t_env *envs, char **cmd, int i)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	if (i > 0)
	{
		if (cmd[i][0] != '"' && cmd[i][0] != '\'')
		{
			if (check_will_splited_helper_ambg1(envs, vars, cmd, i))
				return (1);
		}
		else if (cmd[i][0] == '"' || cmd[i][0] == '\'')
		{
			if (check_will_splited_helper2(envs, vars, cmd, i))
				return (1);
		}
	}
	else
	{
		if (check_will_splited_helper_ambg1(envs, vars, cmd, i))
			return (1);
	}
	return (0);
}
