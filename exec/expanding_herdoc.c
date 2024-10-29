/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_herdoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:59:57 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 16:51:55 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

char	*expanding_herdoc(t_env *envs, char *str, t_path path)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	while (str[vars.i])
	{
		vars.start = vars.i;
		while (str[vars.i] && str[vars.i] != '$')
			vars.i++;
		vars.key = ft_substr(str, vars.start, vars.i - vars.start);
		vars.new = ft_strjoin(vars.new, vars.key);
		if (str[vars.i] == '$')
		{
			count_dollars(&vars, str);
			if (vars.start % 2 == 0)
				add_dollars(&vars, 1);
			else
			{
				add_dollars(&vars, 2);
				double_quotes_helper(envs, &vars, &path, str);
			}
		}
	}
	vars.new = ft_strjoin(vars.new, "\0");
	return (vars.new);
}

char	*expanding_cmd_herdoc(t_env *envs, char *old_cmd, t_path path)
{
	char	*tmp;
	char	*res;
	int		i;

	tmp = NULL;
	res = NULL;
	i = 0;
	tmp = expanding_herdoc(envs, old_cmd, path);
	res = ft_strjoin(res, tmp);
	return (free(old_cmd), res);
}

void	get_right_delimeter_helper(t_vars *vars, char c)
{
	if (vars->del[vars->i][0] == '\'' || vars->del[vars->i][0] == '"')
	{
		c = vars->del[vars->i][0];
		vars->j++;
		while (vars->del[vars->i][vars->j] && vars->del[vars->i][vars->j] != c)
			vars->j++;
		vars->delimeter = ft_strjoin(vars->delimeter,
				ft_substr(vars->del[vars->i], 1, vars->j - 1));
	}
	else if (vars->del[vars->i + 1])
	{
		if (vars->del[vars->i][0] == '$' && vars->del[vars->i][1] == '\0'
			&& (vars->del[vars->i + 1][0] == '"'
				|| vars->del[vars->i + 1][0] == '\''))
		;
		else
			vars->delimeter = ft_strjoin(vars->delimeter, vars->del[vars->i]);
	}
	else
		vars->delimeter = ft_strjoin(vars->delimeter, vars->del[vars->i]);
}

char	*get_right_delimeter(char *s)
{
	t_vars	vars;
	char	c;

	c = 0;
	vars = ft_initialize_vars();
	vars.del = expanding_split(s);
	while (vars.del[vars.i])
	{
		vars.j = 0;
		get_right_delimeter_helper(&vars, c);
		vars.i++;
	}
	if (vars.delimeter)
		vars.delimeter = ft_strjoin(vars.delimeter, "\0");
	return (vars.delimeter);
}

int	check_will_expanded(char *delimter)
{
	int	i;

	i = 0;
	while (delimter[i])
	{
		if (delimter[i] == '"' || delimter[i] == '\'')
			return (0);
		i++;
	}
	return (1);
}
