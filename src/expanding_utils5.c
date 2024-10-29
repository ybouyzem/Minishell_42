/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 04:25:42 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/16 21:30:28 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/minishell_exec.h"

static t_env	*empty_envs(void)
{
	t_env	*env_vars;
	char	*path;
	char	*pwd;

	env_vars = NULL;
	pwd = NULL;
	path = ex_strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin");
	if (!path)
		envp_error(env_vars);
	pwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!pwd || !getcwd(pwd, PATH_MAX))
	{
		envp_error(env_vars);
	}
	add_env_back(&env_vars, new_variable(envp_strdup("PATH", env_vars), path));
	add_env_back(&env_vars, new_variable(envp_strdup("PWD", env_vars), pwd));
	add_env_back(&env_vars, new_variable(
			envp_strdup("SHLVL", env_vars), envp_strdup("1", env_vars)));
	add_env_back(&env_vars, new_variable(
			envp_strdup("OLDPWD", env_vars), NULL));
	add_env_back(&env_vars, new_variable(
			envp_strdup("_", env_vars), envp_strdup("PATH", env_vars)));
	return (env_vars);
}

t_env	*full_envs(char	**env)
{
	int		i;
	t_env	*node;
	t_env	*env_vars;

	if (*env == NULL)
		return (empty_envs());
	env_vars = NULL;
	i = 0;
	while (env[i])
	{
		node = new_variable(get_str(env[i], "key"), get_str(env[i], "value"));
		if (!node)
			envp_error(env_vars);
		add_env_back(&env_vars, node);
		i++;
	}
	update_var(env_vars, "_", ex_strdup("PATH"));
	if (get_env_key(env_vars, "OLDPWD"))
		return (update_var(env_vars, "OLDPWD", NULL), env_vars);
	node = new_variable(ex_strdup("OLDPWD"), NULL);
	if (!node)
		envp_error(env_vars);
	add_env_back(&env_vars, node);
	return (env_vars);
}

int	ft_check_space_in_cmd(char *str)
{
	int		begining;
	t_vars	vars;

	vars = ft_initialize_vars();
	if (!str)
		return (0);
	if (str[0] == '\0')
		return (0);
	begining = 0;
	while (str[vars.i] && ft_isspace(str[vars.i]))
		vars.i++;
	if (vars.i > 0)
		begining = 1;
	vars.len = ft_strlen(str) - 1;
	vars.i = vars.len;
	while (vars.i && ft_isspace(str[vars.i]))
		vars.i--;
	if (vars.len != vars.i && begining == 1)
		return (3);
	else if (begining == 1)
		return (2);
	else if (vars.len != vars.i)
		return (1);
	else
		return (0);
}

int	check_is_joinable(char **cmd, int index)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	while (cmd[index][vars.i])
	{
		if (cmd[index][vars.i] == '$')
		{
			vars.i++;
			vars.start = 1;
			while (cmd[index][vars.i] && cmd[index][vars.i] == '$')
			{
				vars.start++;
				vars.i++;
			}
			if (cmd[index + 1] != NULL)
			{
				if (vars.start % 2 != 0 && cmd[index][vars.i] == '\0'
					&& (cmd[index + 1][0] == '"' || cmd[index + 1][0] == '\''))
					return (1);
			}
		}
		else
			vars.i++;
	}
	return (0);
}

int	check_will_splited(t_env *envs, char **cmd, int i)
{
	t_vars	vars;

	vars = ft_initialize_vars();
	if (i > 0)
	{
		if (cmd[i][0] != '"' && cmd[i][0] != '\'')
		{
			if (check_will_splited_helper1(envs, vars, cmd, i))
				return (1);
		}
		else if (cmd[i][0] == '"' || cmd[i][0] == '\'')
		{
			if (check_will_splited_helper2(envs, vars, cmd, i))
				return (1);
		}
	}
	else
	{
		if (check_will_splited_helper1(envs, vars, cmd, i))
			return (1);
	}
	return (0);
}
