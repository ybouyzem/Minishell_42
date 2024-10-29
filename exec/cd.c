/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 11:03:00 by alamini           #+#    #+#             */
/*   Updated: 2024/10/16 11:01:51 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

int	update_wd(int output, char *old_wd, t_path *path_struct, t_env *env)
{
	char	*cwd;

	cwd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!cwd)
		malloc_error(path_struct, env);
	if (output == 0 && errno == ENOENT)
	{
		printf("cd: error retrieving current directory:");
		printf(" getcwd:cannot access parent directories:");
		printf(" No such file or directory\n");
		chdir(path_struct->main_path);
	}
	if (get_env_key(env, "OLDPWD"))
		update_var(env, "OLDPWD", old_wd);
	else
		add_env_back(&env, new_variable(ft_strdup("OLDPWD"), old_wd));
	getcwd(cwd, PATH_MAX);
	if (get_env_key(env, "PWD"))
		update_var(env, "PWD", cwd);
	else
		add_env_back(&env, new_variable(ft_strdup("PWD"), cwd));
	free(path_struct->pwd);
	path_struct->pwd = ft_strdup(cwd);
	return (0);
}

int	exec_cd(t_env *env, char *var, int check, t_path *path_struct)
{
	char	*old_wd;
	char	*path;
	int		output;

	output = 0;
	path = NULL;
	old_wd = (char *)malloc(sizeof(char) * PATH_MAX);
	if (!old_wd)
		malloc_error(path_struct, env);
	getcwd(old_wd, PATH_MAX);
	if (!check)
		path = get_env_value(env, var);
	else
		path = var;
	if (!path)
		return (print_error("cd", var, "not set"), free(old_wd), 1);
	output = chdir(path);
	if (output == -1)
		return (print_error("cd", path, strerror(errno)), free(old_wd), 1);
	else
		update_wd(output, old_wd, path_struct, env);
	return (0);
}

int	cd(t_command *command, t_env *env, t_path *path)
{
	if (!command->cmd[1] || ex_strcmp(command->cmd[1], "~") == 0)
	{
		if (exec_cd(env, "HOME", 0, path))
			return (1);
	}
	else if (ex_strcmp(command->cmd[1], "-") == 0)
	{
		if (exec_cd(env, "OLDPWD", 0, path))
			return (1);
		else
			printf("%s\n", get_env_value(env, "PWD"));
	}
	else
	{
		if (exec_cd(env, command->cmd[1], 1, path))
			return (1);
	}
	return (0);
}
