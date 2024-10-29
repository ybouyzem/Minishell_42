/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 05:46:27 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 13:47:25 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

void	skip_dollars(char **cmd, int i, int *j, int *nbr)
{
	*j += 1;
	*nbr = 1;
	while (cmd[i][*j] == '$' && cmd[i][*j])
	{
		*nbr += 1;
		*j += 1;
	}
}

int	check_will_splited_helper1(t_env *envs, t_vars vars, char **cmd, int i)
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
				if (ft_check_space_in_cmd(vars.value) > 0
					|| split_count_words(vars.value) > 1)
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

void	check_helper2_1(t_env *envs, t_vars *vars, char **cmd, int i)
{
	skip_dollars(cmd, i - 1, &vars->j, &vars->nbr);
	if (vars->nbr % 2 != 0)
	{
		vars->start = vars->j;
		while (cmd[i - 1][vars->j] && ft_isalpha(cmd[i - 1][vars->j]) &&
			cmd[i - 1][vars->j] != '"')
			vars->j++;
		vars->key
			= ft_substr(cmd[i - 1], vars->start, vars->j - vars->start + 1);
		vars->value = get_env_variable(envs, vars->key);
		if ((ft_check_space_in_cmd(vars->value) > 0
				|| (split_count_words(vars->value) > 1
					&& ft_check_space_in_cmd(cmd[i]) > 0
					&& ft_check_space_in_cmd(cmd[i - 1]) == 0)))
			vars->check = 1;
	}
	else
		vars->check = 0;
}

int	check_will_splited_helper2(t_env *envs, t_vars vars, char **cmd, int i)
{
	while (cmd[i - 1][vars.j])
	{
		if (cmd[i - 1][vars.j] == '$')
			check_helper2_1(envs, &vars, cmd, i);
		else
			vars.j++;
	}
	return (vars.check);
}

int	check_will_splited_helper3(t_vars vars, char **cmd, int i)
{
	while (cmd[i][vars.j])
	{
		if (cmd[i][vars.j] == '$' && ft_isalpha(cmd[i][vars.j + 1]))
			vars.check = 1;
		vars.j++;
	}
	if (vars.check == 1)
		return (1);
	return (0);
}
