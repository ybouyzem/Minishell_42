/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouyzem <ybouyzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 05:05:44 by alamini           #+#    #+#             */
/*   Updated: 2024/10/27 09:42:28 by ybouyzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

void	exit_status(int status, t_path *path)
{
	path->exit_status = status;
	g_last_signal = 0;
	return ;
}

void	set_last_arg(t_command *command, t_env **env_vars)
{
	t_command	*current;
	int			i;

	i = 0;
	current = command;
	if (!current || !current->cmd[0])
		return ;
	while (current->cmd[i])
		i++;
	if (!current->cmd[i] && i == 1
		&& ex_strcmp(current->cmd[i - 1], "echo") == 0)
	{
		update_var(*env_vars, "_", ex_strdup("\0"));
	}
	else
		update_var(*env_vars, "_", ex_strdup(current->cmd[i - 1]));
}

void	reset_fd(t_path *path)
{
	if (path->fd_in != 0)
	{
		dup2(path->fd_in, STDIN_FILENO);
		close(path->fd_in);
	}
	if (path->fd_out != 1)
	{
		dup2(path->fd_out, STDOUT_FILENO);
		close(path->fd_out);
	}
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ex_strcmp("cd", cmd) == 0
		|| ex_strcmp("pwd", cmd) == 0
		|| ex_strcmp("echo", cmd) == 0
		|| ex_strcmp("echo", cmd) == 0
		|| ex_strcmp("export", cmd) == 0
		|| ex_strcmp("env", cmd) == 0
		|| ex_strcmp("unset", cmd) == 0
		|| ex_strcmp("exit", cmd) == 0)
		return (1);
	return (0);
}

int	ambigous_case(t_command *command, t_path *path, int i)
{
	int	pos;

	pos = -1;
	if (command->is_ambiguous != -1)
		pos = command->is_ambiguous - ft_strslen(command->cmd);
	if (pos == i + 1)
	{
		print_error(command->ambiguous_file, NULL, "ambiguous redirect");
		if (path->is_forked)
			exit(1);
		else
			return (1);
	}
	return (0);
}
