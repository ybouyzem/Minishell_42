/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:29:13 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/15 11:12:09 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

char	**join_two_double_strs(char **s1, char **s2)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	if (!s2)
		return (s1);
	if (!s1)
		return (s2);
	if (!s1 && !s2)
		return (NULL);
	vars.len = ft_strslen(s1) + ft_strslen(s2);
	vars.res = ft_allocate(vars.len);
	while (s1[vars.i])
	{
		vars.res[vars.i] = my_strdup(s1[vars.i]);
		vars.i++;
	}
	while (s2[vars.j])
		vars.res[vars.i++] = my_strdup(s2[vars.j++]);
	vars.res[vars.i] = 0;
	return (vars.res);
}

char	**join_double_with_str(char **s1, char *s2)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	if (!s2)
		return (s1);
	if (!s1 || !*s1)
	{
		vars.res = (char **)my_malloc(sizeof(char *) * 2, 1);
		if (!vars.res)
			return (my_malloc(0, 0), exit(10), NULL);
		vars.res[0] = s2;
		vars.res[1] = NULL;
		return (vars.res);
	}
	vars.res = (char **)my_malloc(sizeof(char *) * (ft_strslen(s1) + 2), 1);
	if (!vars.res)
		return (my_malloc(0, 0), exit(10), NULL);
	while (s1[vars.i])
	{
		vars.res[vars.i] = my_strdup(s1[vars.i]);
		vars.i++;
	}
	vars.res[vars.i++] = my_strdup(s2);
	vars.res[vars.i] = 0;
	return (vars.res);
}

int	get_last_quote_pos(char	*old_cmd)
{
	int	len;

	len = ft_strlen(old_cmd);
	while (len && old_cmd[len] != '"')
		len--;
	return (len);
}

char	*single_quotes_process(char *str)
{
	int		i;
	char	*res;

	res = NULL;
	i = 0;
	str++;
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\'')
		str[i] = '\0';
	res = ft_strjoin(res, str);
	return (res);
}

char	**single_quotes(t_env *envs, t_vars vars, int *index)
{
	char	*tmp;
	char	**temp;

	temp = NULL;
	tmp = NULL;
	tmp = single_quotes_process(vars.cmd[vars.i]);
	*index = ft_strslen(vars.res);
	if (tmp && tmp[0] != '\0'
		&& check_will_splited(envs, vars.cmd, vars.i) == 1)
	{
		temp = ft_split(tmp, ' ');
		vars.res = join_two_double_strs(vars.res, temp);
	}
	else
	{
		if (!vars.res)
			vars.res = join_double_with_str(vars.res, tmp);
		else
		{
			vars.res[*index - 1] = ft_strjoin(vars.res[*index - 1], tmp);
			vars.res[*index] = 0;
		}
	}
	return (vars.res);
}
