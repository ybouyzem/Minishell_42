/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 08:41:32 by alamini           #+#    #+#             */
/*   Updated: 2024/10/20 13:45:43 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

static int	create_pipe(int *fd)
{
	if (pipe(fd) < 0)
	{
		printf("Error :Pipe No created !!");
		exit(1);
	}
	return (0);
}

static void	fork_failure(int *pipe_fds, int *input_fd, t_path *path)
{
	write(2, "Fork error: Not enough resources\n", 34);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	close(*input_fd);
	exit_status(1, path);
	while (waitpid(-1, NULL, 0) > 0)
		;
	return ;
}

static int	child_process(t_command *cmd, t_env **env, int *input_fd,
	t_path *path)
{
	setup_signals(UNSET_SIG);
	if (*input_fd != -1)
	{
		if (dup2(*input_fd, STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (1);
		}
		close(*input_fd);
	}
	if (cmd->next)
	{
		if (dup2(cmd->pipe[1], STDOUT_FILENO) < 0)
			return (perror("dup2"), 1);
		close(cmd->pipe[0]);
		close(cmd->pipe[1]);
	}
	if (cmd->redirection[0])
		handle_redirection(cmd, path);
	check_command(cmd, env, path);
	exit(0);
}

static int	parent_process(t_command *cmd, int *input_fd)
{
	if (*input_fd != -1)
		close(*input_fd);
	if (cmd->next)
	{
		close(cmd->pipe[1]);
		*input_fd = cmd->pipe[0];
	}
	else
		close(cmd->pipe[0]);
	return (0);
}

int	piping(t_command *cmd, t_env **env, int *input_fd, t_path *path)
{
	int	pid;

	if (cmd->next)
		create_pipe(cmd->pipe);
	pid = fork();
	if (pid < 0)
	{
		fork_failure(cmd->pipe, input_fd, path);
		return (1);
	}
	path->is_forked = 1;
	if (pid == 0)
	{
		if (child_process(cmd, env, input_fd, path))
			return (0);
	}
	else
	{
		if (parent_process(cmd, input_fd))
			return (0);
	}
	return (0);
}
