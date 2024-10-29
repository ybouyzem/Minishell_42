/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:31:52 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/20 13:29:46 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <fcntl.h>
# include "minishell.h"
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <sys/stat.h>

// utils
char	**my_split(char const *s, char c);
int		ex_strcmp(char *s1, char *s2);
char	*ex_strjoin(char *s1, char *s2);
char	*special_join(char *s1, char *s2);
size_t	ex_strlen(const char *s);
char	*ex_strdup(const char *s1);
char	*my_strdup(const char *s1);
char	*my_strjoin(char *s1, char *s2);
char	*my_itoa(int n);
void	print_error(char *cmd, char *path, char *error);
int		ft_is_numeric(char *s);
int		occur_alpha(char *str, int c);
void	reset_fd(t_path *path);
int		is_builtin(char *cmd);
void	malloc_error(t_path *path, t_env *env);
void	fd_error(t_path *path, t_env *env);
char	*my_get_key(char *str);
char	*my_get_value(char *str);
char	*my_get_sep(char *str);
// list utils
t_env	*env_vars_copy(t_env **env_vars);
int		list_size(t_env *lst);
void	sort_vars(t_env **env_vars);
void	update_var(t_env *env, char *env_key, char *new_value);
char	*get_env_value(t_env *env, char *env_key);
char	*get_env_key(t_env *env, char *env_key);
char	**envp_array(t_env *vars);
void	error_exit(t_env **head);
void	envp_error(t_env *env);
void	env_dataclear(t_env **head);
char	*envp_strdup(const char *s1, t_env *env);
// other utils
void	exit_status(int status, t_path *path);
void	set_last_arg(t_command *command, t_env **env_vars);
// comannds 
void	check_command(t_command *command, t_env **env_vars, t_path *path);
// builtins 
int		cd(t_command *command, t_env *env_vars, t_path *path);
int		echo(t_command *command);
int		env(t_command *command, t_env *env_vars);
int		pwd(t_path *path);
int		export(t_command *cmds, t_env **env_vars);
int		unset(t_command *cmds, t_env **env_vars);
void	exit_shell(t_command *command, t_path *path);
// redirections 
int		handle_redirection(t_command *command, t_path *path);
int		ambigous_case(t_command *command, t_path *path, int i);
// piping 
int		piping(t_command *command, t_env **env_vars,
			int *input_fd, t_path *path);
#endif