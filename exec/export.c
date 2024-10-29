/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:09:45 by alamini           #+#    #+#             */
/*   Updated: 2024/10/15 16:20:14 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

static void	export_display(t_env **env_vars)
{
	t_env	*env_copy;
	t_env	*tmp;

	env_copy = env_vars_copy(env_vars);
	tmp = env_copy;
	sort_vars(&env_copy);
	while (env_copy)
	{
		if (ex_strcmp(env_copy->key, "_") == 0)
		{
			env_copy = env_copy->next;
			continue ;
		}
		if (env_copy->value)
			printf("declare -x %s=\"%s\"\n", env_copy->key, env_copy->value);
		else
			printf("declare -x %s\n", env_copy->key);
		env_copy = env_copy->next;
	}
	free_envs(tmp);
}

static int	export_syntax(char *key)
{
	int	i;

	i = 0;
	if (!key)
		return (1);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (1);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	update_key(char *cmd, t_env **env)
{
	char	*value;

	value = NULL;
	if (ft_strcmp(my_get_key(cmd), "_") == 0)
		value = ft_strdup("_");
	else
	{
		if (ex_strcmp(my_get_sep(cmd), "+=") == 0)
		{
			value = get_env_value(*env, my_get_key(cmd));
			value = special_join(value, my_get_value(cmd));
		}
		else if (my_get_value(cmd))
			value = get_str(cmd, "value");
	}
	if (value)
		update_var(*env, my_get_key(cmd), value);
}

int	export(t_command *cmds, t_env **env)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	if (cmds->cmd[i])
	{
		while (cmds->cmd[i])
		{
			if (export_syntax(my_get_key(cmds->cmd[i])))
			{
				print_error("export", cmds->cmd[i], "not a valid identifier");
				exit_status = 1;
			}
			else if (get_env_key(*env, my_get_key(cmds->cmd[i])))
				update_key(cmds->cmd[i], env);
			else
				add_env_back(env, new_variable(get_str(cmds->cmd[i], "key"),
						get_str(cmds->cmd[i], "value")));
			i++;
		}
	}
	else
		export_display(env);
	return (exit_status);
}

int	unset(t_command *cmds, t_env **env_vars)
{
	int		i;
	char	*key;
	int		exit_status;

	i = 1;
	exit_status = 0;
	while (cmds->cmd[i])
	{
		key = my_strdup(cmds->cmd[i]);
		if (export_syntax(key))
		{
			print_error("unset", cmds->cmd[i], ":not a valid identifier");
			exit_status = 1;
		}
		else
		{
			if (ex_strcmp(key, "_") != 0)
				delete_env(env_vars, cmds->cmd[i]);
		}
		i++;
	}
	return (exit_status);
}
