/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 10:21:54 by alamini           #+#    #+#             */
/*   Updated: 2024/10/15 13:31:43 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

static void	execution(char *cmd, char **args, char **envp, t_path *path)
{
	if (execve(cmd, args, envp) == -1)
	{
		print_error(cmd, NULL, strerror(errno));
		exit_status(1, path);
		exit(path->exit_status);
	}
}

static void	actual_bin_dir(t_command *command, char **envp, t_path *path)
{
	struct stat	statbuf;
	char		*cmd;

	cmd = command->cmd[0];
	if (access(cmd, F_OK) != 0)
	{
		print_error(cmd, NULL, "No such file or directory");
		exit(127);
	}
	stat(cmd, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		print_error(cmd, NULL, "is a directory");
		exit(126);
	}
	if (access(cmd, X_OK) != 0)
	{
		print_error(cmd, NULL, "Permission denied");
		exit(126);
	}
	if (statbuf.st_size == 0)
		exit(0);
	execution(cmd, command->cmd, envp, path);
}

static void	commands(t_command *command, t_env **env, char **envp, t_path *path)
{
	char	**ptr;
	int		i;

	i = 0;
	if (ex_strlen(command->cmd[0]) == 0)
	{
		print_error(command->cmd[0], NULL, "command not found");
		exit_status(127, path);
		exit(path->exit_status);
	}
	if (occur_alpha(command->cmd[0], '/') || command->cmd[0][0] == '.'
		|| ex_strlen(get_env_value(*env, "PATH")) < 1)
		actual_bin_dir(command, envp, path);
	ptr = my_split(get_env_value(*env, "PATH"), ':');
	while (ptr[i])
	{
		ptr[i] = my_strjoin(ptr[i], "/");
		ptr[i] = my_strjoin(ptr[i], command->cmd[0]);
		if (access(ptr[i], X_OK) == 0)
			execution(ptr[i], command->cmd, envp, path);
		i++;
	}
	print_error(command->cmd[0], NULL, "command not found");
	exit(127);
}

void	check_command(t_command *command, t_env **env_vars, t_path *path)
{
	if (!command->cmd[0])
		return ;
	if (ex_strcmp("cd", command->cmd[0]) == 0)
		exit_status(cd(command, *env_vars, path), path);
	else if (ex_strcmp("pwd", command->cmd[0]) == 0)
		exit_status(pwd(path), path);
	else if (ex_strcmp("echo", command->cmd[0]) == 0)
		exit_status(echo(command), path);
	else if (ex_strcmp("export", command->cmd[0]) == 0)
		exit_status(export(command, env_vars), path);
	else if (ex_strcmp("env", command->cmd[0]) == 0)
		exit_status(env(command, *env_vars), path);
	else if (ex_strcmp("unset", command->cmd[0]) == 0)
		exit_status(unset(command, env_vars), path);
	else if (ex_strcmp("exit", command->cmd[0]) == 0)
		exit_shell(command, path);
	else
		commands(command, env_vars, envp_array(*env_vars), path);
}
