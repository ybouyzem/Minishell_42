/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redrection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 09:44:22 by alamini           #+#    #+#             */
/*   Updated: 2024/10/14 17:12:08 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_exec.h"

static int	std_out(t_command *command, int pos, t_path *path)
{
	int	fd;

	if (path->fd_out == 1)
		path->fd_out = dup(STDOUT_FILENO);
	fd = open(command->redirection[pos], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		print_error(command->redirection[pos], NULL, strerror(errno));
		exit_status(1, path);
		if (path->is_forked)
			exit(1);
		else
			return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	std_out_append(t_command *command, int pos, t_path *path)
{
	int	fd;

	if (path->fd_out == 1)
		path->fd_out = dup(STDOUT_FILENO);
	fd = open(command->redirection[pos], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		print_error(command->redirection[pos], NULL, strerror(errno));
		exit_status(1, path);
		if (path->is_forked)
			exit(1);
		else
			return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	std_in(t_command *command, int pos, t_path *path)
{
	int	fd;

	if (path->fd_in == 0)
		path->fd_in = dup(STDIN_FILENO);
	fd = open(command->redirection[pos], O_RDONLY);
	if (fd == -1)
	{
		print_error(command->redirection[pos], NULL, strerror(errno));
		exit_status(1, path);
		if (path->is_forked)
			exit(1);
		else
			return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	redirect_heredoc(t_command *command, t_path *path)
{
	int	fd;

	fd = open(command->last_file, O_RDONLY);
	if (fd == -1)
	{
		print_error("heredoc", NULL, strerror(errno));
		exit_status(1, path);
		if (path->is_forked)
			exit(1);
		else
			return (1);
	}
	if (path->fd_in == 0)
		path->fd_in = dup(STDIN_FILENO);
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_redirection(t_command *cmd, t_path *path)
{
	int	i;

	i = 0;
	while (cmd->redirection[i])
	{
		if (ex_strcmp(cmd->redirection[i], ">") == 0)
		{
			if (ambigous_case(cmd, path, i) || std_out(cmd, i + 1, path))
				return (1);
		}
		else if (ex_strcmp(cmd->redirection[i], ">>") == 0)
		{
			if (ambigous_case(cmd, path, i) || std_out_append(cmd, i + 1, path))
				return (1);
		}
		else if (ex_strcmp(cmd->redirection[i], "<") == 0)
		{
			if (ambigous_case(cmd, path, i) || std_in(cmd, i + 1, path) == 1)
				return (1);
		}
		else if (ex_strcmp(cmd->redirection[i], "<<") == 0)
			redirect_heredoc(cmd, path);
		i++;
	}
	return (0);
}
