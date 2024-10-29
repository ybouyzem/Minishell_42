/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 12:55:50 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/17 11:23:07 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

void	expanding_cmd_helper(t_env *envs, t_vars *vars)
{
	if (vars->cmd[vars->i][0] == '"' || (vars->cmd[vars->i][0] != '"'
		&& !is_only_spaces(vars->tmp)))
	{
		if (vars->tmp && vars->tmp[0] != '\0'
			&& check_will_splited(envs, vars->cmd, vars->i)
			&& vars->cmd[vars->i][0] != '"')
		{
			vars->temp = ft_split(vars->tmp, ' ');
			vars->res = join_two_double_strs(vars->res, vars->temp);
		}
		else
		{
			if (!vars->res)
				vars->res = join_double_with_str(vars->res, vars->tmp);
			else
			{
				vars->index = ft_strslen(vars->res);
				vars->res[vars->index - 1]
					= ft_strjoin(vars->res[vars->index - 1], vars->tmp);
				vars->res[vars->index] = 0;
			}
		}
	}
	else
		vars->res = join_double_with_str(vars->res, vars->tmp);
}

char	**expanding_cmd(t_env *envs, char *old_cmd, t_path *path, int is_pipe)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	vars.cmd = expanding_split(old_cmd);
	while (vars.cmd[vars.i])
	{
		if (vars.cmd[vars.i][0] == '\'')
			vars.res
				= single_quotes(envs, vars, &vars.index);
		else
		{
			if (check_is_joinable(vars.cmd, vars.i))
				vars.cmd[vars.i][ft_strlen(vars.cmd[vars.i]) - 1] = '\0';
			vars.tmp = double_quotes_p(envs, vars.cmd[vars.i], path, is_pipe);
			if ((vars.tmp[0] == '\0' && vars.cmd[vars.i][0] == '"')
				|| vars.tmp[0] != '\0')
				expanding_cmd_helper(envs, &vars);
		}
		vars.i++;
	}
	return (vars.res);
}

void	expanding_red_hlp(t_env *envs, t_vars *vars, t_command *node, t_vars v)
{
	if (vars->tmp && vars->tmp[0] == '*'
		&& vars->cmd[vars->i][0] != '"' && vars->tmp[1] == '\0')
	{
		node->is_ambiguous = v.start;
		node->ambiguous_file = v.res[v.start];
	}
	else if (vars->tmp && vars->tmp[0] != '\0'
		&& check_will_splited_ambg(envs, vars->cmd, vars->i)
		&& vars->cmd[vars->i][0] != '"')
	{
		node->is_ambiguous = v.start;
		node->ambiguous_file = v.res[v.start];
	}
	else
	{
		if (!vars->res)
			vars->res = join_double_with_str(vars->res, vars->tmp);
		else
		{
			vars->index = ft_strslen(vars->res);
			vars->res[vars->index - 1]
				= ft_strjoin(vars->res[vars->index - 1], vars->tmp);
			vars->res[vars->index] = 0;
		}
	}
}

void	expanding_red_hlp2(t_command *node, t_env *envs, t_vars *vars, t_vars v)
{
	if ((vars->tmp[0] == '\0' && vars->cmd[vars->i][0] == '"')
		|| vars->tmp[0] != '\0')
	{
		if (vars->cmd[vars->i][0] == '"' || (vars->cmd[vars->i][0] != '"'
			&& !is_only_spaces(vars->tmp)))
			expanding_red_hlp(envs, vars, node, v);
		else
			vars->res = join_double_with_str(vars->res, vars->tmp);
	}
	else
	{
		if (vars->i == 0 && vars->cmd[vars->i + 1] == NULL)
		{
			node->is_ambiguous = v.start;
			node->ambiguous_file = v.res[v.start];
		}
	}
}

char	**expanding_red(t_command *node, t_env *envs, t_path *path, t_vars v)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	vars.cmd = expanding_split(v.res[v.start]);
	while (vars.cmd[vars.i])
	{
		if (vars.cmd[vars.i][0] == '\'')
			vars.res
				= single_quotes(envs, vars, &vars.index);
		else
		{
			if (check_is_joinable(vars.cmd, vars.i))
				vars.cmd[vars.i][ft_strlen(vars.cmd[vars.i]) - 1] = '\0';
			vars.tmp = double_quotes_p(envs, vars.cmd[vars.i], path, -1);
			expanding_red_hlp2(node, envs, &vars, v);
		}
		vars.i++;
	}
	return (vars.res);
}
