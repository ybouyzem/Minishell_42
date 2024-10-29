/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:36:56 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 13:43:47 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

void	add_string(t_vars *vars, char *str)
{
	vars->start = vars->i;
	while (str[vars->i] && str[vars->i] != '$' && str[vars->i] != '"')
		vars->i++;
	vars->key = ft_substr(str, vars->start, vars->i - vars->start);
	vars->new = ft_strjoin(vars->new, vars->key);
}

void	exit_status_case(t_vars *vars, t_path *path, int is_pipe)
{
	if (g_last_signal == SIGINT)
	{
		vars->new = ft_strjoin(vars->new, "1");
		g_last_signal = 0;
	}
	else if (is_pipe > 0)
		vars->new = ft_strjoin(vars->new, "0");
	else
	{
		vars->value = ft_itoa(path->exit_status);
		vars->new = ft_strjoin(vars->new, vars->value);
	}
	vars->i++;
}

void	last_command_case(t_vars *vars, t_env *envs)
{
	if (vars->is_pipe > 0)
		vars->new = ft_strjoin(vars->new, "\0");
	else
	{
		vars->value = get_env_variable(envs, "_");
		if (vars->value)
			vars->new = ft_strjoin(vars->new, vars->value);
	}
}

void	double_quotes_helper(t_env *envs, t_vars *vars, t_path *path, char *str)
{
	if (str[vars->i] == '?')
		exit_status_case(vars, path, vars->is_pipe);
	else if (ft_isdigit(str[vars->i]))
		vars->i++;
	else if (str[vars->i] == '_' && !ft_isalnum(str[vars->i + 1]))
	{
		last_command_case(vars, envs);
		vars->i++;
	}
	else
	{
		if (!ft_isalnum(str[vars->i]) && str[vars->i] != '_')
			vars->new = ft_strjoin(vars->new, "$");
		vars->start = vars->i;
		while ((ft_isalnum(str[vars->i])
				|| str[vars->i] == '_') && str[vars->i])
			vars->i++;
		vars->key = ft_substr(str, vars->start, vars->i - vars->start);
		vars->value = get_env_variable(envs, vars->key);
		if (vars->value)
			vars->new = ft_strjoin(vars->new, vars->value);
	}
}

char	*double_quotes_p(t_env *envs, char *str, t_path *path, int is_pipe)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	vars.is_pipe = is_pipe;
	if (str[0] == '"')
		str++;
	while (str[vars.i] && str[vars.i] != '"')
	{
		add_string(&vars, str);
		if (str[vars.i] == '$')
		{
			count_dollars(&vars, str);
			if (vars.start % 2 == 0)
				add_dollars(&vars, 1);
			else
			{
				add_dollars(&vars, 2);
				double_quotes_helper(envs, &vars, path, str);
			}
		}
	}
	vars.new = ft_strjoin(vars.new, "\0");
	return (vars.new);
}
