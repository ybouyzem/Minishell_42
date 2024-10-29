/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 01:44:49 by alamini           #+#    #+#             */
/*   Updated: 2024/10/20 15:31:53 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

static void	exec_builtin(t_command *current, t_env **env, t_path *path)
{
	int	check;

	check = 0;
	path->is_forked = 0;
	if (current->redirection[0])
		check = handle_redirection(current, path);
	if (!check)
	{
		check_command(current, env, path);
	}
	if (current->redirection[0])
		reset_fd(path);
	return ;
}

static void	waiting_processes(t_path *path)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1 && errno != ECHILD)
	{
		if (WIFEXITED(status))
			exit_status(WEXITSTATUS(status), path);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
			{
				exit_status(130, path);
				printf("\n");
			}
			else if (WTERMSIG(status) == 3)
			{
				exit_status(131, path);
				printf("Quit: 3\n");
			}
		}
	}
}

static void	no_command(t_command *current, t_path *path)
{
	if (current->redirection[0])
	{
		handle_redirection(current, path);
		reset_fd(path);
	}
}

void	execute(t_command *command, t_env **env, t_path *path)
{
	t_command	*current;
	int			input_fd;

	current = command;
	input_fd = -1;
	path->fd_in = 0;
	path->fd_out = 1;
	while (current)
	{
		set_last_arg(current, env);
		if (handle_herdoc(current, path, env, input_fd))
			return ;
		if (!current->cmd[0] && path->is_forked == 0)
			no_command(current, path);
		else if (is_builtin(current->cmd[0]) && !current->next
			&& path->is_forked == 0)
		{
			exec_builtin(current, env, path);
		}
		else
			if (piping(current, env, &input_fd, path))
				return ;
		current = current->next;
	}
	waiting_processes(path);
}
