/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:51:44 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 16:24:53 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

int	my_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0'
		&& s2[i] != '\0' && s2[i] != '\'' && s2[i] != '"')
		i++;
	return (s1[i] - s2[i]);
}

char	*get_env_variable(t_env *env, char *env_key)
{
	t_env	*tmp;

	tmp = env;
	if (!env || !env_key)
		return (NULL);
	while (tmp)
	{
		if (my_strcmp(tmp->key, env_key) == 0)
			return (my_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

t_vars	ft_initialize_vars(void)
{
	t_vars	vars;

	vars.i = 0;
	vars.j = 0;
	vars.nbr = 0;
	vars.index = 0;
	vars.start = 0;
	vars.len = 0;
	vars.check = 0;
	vars.is_pipe = 0;
	vars.single_quote = 0;
	vars.double_quote = 0;
	vars.input = NULL;
	vars.tmp = NULL;
	vars.new = NULL;
	vars.key = NULL;
	vars.value = NULL;
	vars.delimeter = NULL;
	vars.res = NULL;
	vars.cmd = NULL;
	vars.temp = NULL;
	vars.args = NULL;
	vars.del = NULL;
	return (vars);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	check_quotes_existed(char *old_cmd)
{
	int	i;

	i = 0;
	while (old_cmd[i] && old_cmd[i] != '"' && old_cmd[i] != '\'')
		i++;
	if (old_cmd[i] == '\'')
		return (1);
	if (old_cmd[i] == '"')
		return (2);
	return (0);
}
