/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 08:47:16 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/15 11:12:43 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_command_helper(t_command *node, t_env *envs, t_vars *vars, t_path *path)
{
	if (ft_is_red(vars->res[vars->start]))
	{
		node->redirection
			= join_double_with_str(node->redirection, vars->res[vars->start]);
		vars->start++;
		vars->temp = expanding_red(node, envs, path, *vars);
		node->redirection = join_two_double_strs(node->redirection, vars->temp);
		vars->start++;
		return (1);
	}
	else if (!ft_strcmp(vars->res[vars->start], "<<"))
	{
		node->redirection
			= join_double_with_str(node->redirection, vars->res[vars->start]);
		vars->start++;
		node->redirection
			= join_double_with_str(node->redirection, vars->res[vars->start]);
		vars->start++;
		return (1);
	}
	else
		return (0);
}

void	get_command_helper2(t_command *node)
{
	if (node->redirection == NULL)
	{
		node->redirection = (char **)my_malloc(sizeof(char *), 1);
		if (!node->redirection)
			(my_malloc(0, 0), exit(10));
		node->redirection[0] = 0;
	}
	if (node->cmd == NULL)
	{
		node->cmd = (char **)my_malloc(sizeof(char *), 1);
		if (!node->cmd)
			(my_malloc(0, 0), exit(10));
		node->cmd[0] = 0;
	}
}

t_command	*get_command(char **args, t_env *envs, t_vars vars, t_path *path)
{
	t_command	*node;
	static int	i;

	node = allocate_node();
	vars.res = args;
	while (vars.start < vars.i && args[vars.start])
	{
		if (!get_command_helper(node, envs, &vars, path))
		{
			vars.temp = expanding_cmd(envs, vars.res[vars.start], path, i);
			node->cmd = join_two_double_strs(node->cmd, vars.temp);
			vars.start++;
		}
	}
	get_command_helper2(node);
	i++;
	if (!args[vars.i])
		i = 0;
	return (node);
}

void	split_cmd_helper(t_vars *vars)
{
	vars->i++;
	vars->start = vars->i;
}

t_command	*split_cmds(char **args, t_env *envs, t_path *path)
{
	t_command	*input;
	t_command	*node;
	t_vars		vars;

	vars = ft_initialize_vars();
	while (args[vars.i])
	{
		if (ft_strcmp(args[vars.i], "|") == 0 || !args[vars.i])
		{
			if (vars.start < vars.i)
			{
				node = get_command(args, envs, vars, path);
				lstadd_back(&input, node);
			}
			split_cmd_helper(&vars);
		}
		else
			vars.i++;
	}
	if (vars.start < vars.i)
	{
		node = get_command(args, envs, vars, path);
		lstadd_back(&input, node);
	}
	return (input);
}
