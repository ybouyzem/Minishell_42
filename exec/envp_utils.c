/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:58:31 by alamini           #+#    #+#             */
/*   Updated: 2024/10/14 01:57:56 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

char	*get_env_value(t_env *env, char *env_key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, env_key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_env_key(t_env *env, char *env_key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, env_key) == 0)
			return (tmp->key);
		tmp = tmp->next;
	}
	return (NULL);
}

void	update_var(t_env *env, char *env_key, char *new_value)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ex_strcmp(tmp->key, env_key) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = new_value;
			return ;
		}
		tmp = tmp->next;
	}
	return ;
}

char	**envp_array(t_env *vars)
{
	t_env	*tmp;
	char	**envp;
	int		i;
	char	*str;

	i = 0;
	tmp = vars;
	envp = (char **)my_malloc(sizeof(char *) * (list_size(tmp) + 1), 1);
	while (tmp)
	{
		str = my_strjoin(my_strdup("="), my_strdup(tmp->value));
		envp[i] = my_strjoin(my_strdup(tmp->key), str);
		i++;
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
