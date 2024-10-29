/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:48:58 by alamini           #+#    #+#             */
/*   Updated: 2024/10/16 17:00:24 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

t_env	*env_vars_copy(t_env **env_vars)
{
	t_env	*vars_copy;
	t_env	*tmp;

	tmp = *env_vars;
	vars_copy = NULL;
	while (tmp)
	{
		add_env_back(&vars_copy, new_variable(ft_strdup(tmp->key),
				ft_strdup(tmp->value)));
		tmp = tmp->next;
	}
	return (vars_copy);
}

void	sort_vars(t_env **env_vars)
{
	int		i;
	t_env	*current;
	char	*key_tmp;
	char	*value_tmp;

	i = 0;
	current = *env_vars;
	while (i++ < list_size(*env_vars))
	{
		current = *env_vars;
		while (current->next)
		{
			if (ex_strcmp(current->key, current->next->key) > 0)
			{
				key_tmp = current->key;
				value_tmp = current->value;
				current->key = current->next->key;
				current->value = current->next->value;
				current->next->key = key_tmp;
				current->next->value = value_tmp;
			}
			current = current->next;
		}
	}
	return ;
}

int	list_size(t_env *lst)
{
	int		i;
	t_env	*p;

	p = lst;
	i = 0;
	while (p != NULL)
	{
		i++;
		p = p->next;
	}
	return (i);
}

char	*envp_strdup(const char *s1, t_env *env)
{
	char	*ptr;
	int		size;
	int		i;

	size = ex_strlen(s1);
	ptr = malloc((sizeof(char) * (size + 1)));
	if (!ptr)
		return (envp_error(env), NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
