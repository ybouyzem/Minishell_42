/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alamini <alamini@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 22:27:24 by ybouyzem          #+#    #+#             */
/*   Updated: 2024/10/20 15:22:56 by alamini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <termios.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>

# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_BOLD_GREEN "\x1b[1;32m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"
# define AMBIGOUS_INDEX -1

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_command
{
	char				**cmd;
	char				**redirection;
	char				*last_file;
	int					pipe[2];
	int					is_ambiguous;
	char				*ambiguous_file;
	struct s_command	*next;
}	t_command;

typedef struct s_vars
{
	int		i;
	int		j;
	int		nbr;
	int		start;
	int		index;
	int		len;
	int		check;
	int		is_pipe;
	int		single_quote;
	int		double_quote;
	char	*input;
	char	*tmp;
	char	*new;
	char	*key;
	char	*value;
	char	*delimeter;
	char	**res;
	char	**cmd;
	char	**temp;
	char	**args;
	char	**del;
}	t_vars;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*file;
	char				*buffer;
	int					will_expand;
	struct s_heredoc	*next;
}	t_heredoc;

typedef struct s_path
{
	int					exit_status;
	int					is_forked;
	int					fd_in;
	int					fd_out;
	char				*pwd;
	char				*main_path;
	struct s_heredoc	*heredoc;
}	t_path;

typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

enum
{
	ATTR_SET,
	ATTR_GET,
	ATTR_CHG
};

enum
{
	SET_SIG,
	UNSET_SIG,
	HERDOC_SIG
};

int			g_last_signal;
void		syn_err_messages(int code);
int			is_redirection(char *str, int index);
int			check_syntax(char *input);
int			check_quotes(char	*input);
int			ft_isspace(char c);
void		remove_spaces(char **input);
char		*add_spaces(char *input, int single_quote, int double_quote);
char		**split_args(char *s);
void		ft_check_quotes(int *single_quote, int *double_quote, char c);
t_command	*split_cmds(char **args, t_env *env_vars, t_path *path);
int			ft_strslen(char **map);
int			ft_strcmp(char *s1, char *s2);
char		*concat_strs(char *s1, char *s2);
int			split_count_words(const char *s);
// list
void		lstadd_back(t_command **lst, t_command *new);
int			lstsize(t_command *lst);
t_command	*lstlast(t_command *lst);
void		print_list(t_command *lst);

//free
void		free_envs(t_env *envs);
void		free_and_exit(t_path *path, t_env *env_vars);

//expanding
char		**expanding_cmd(t_env *envs, char *old_cmd,
				t_path *path, int is_pipe);
char		**expanding_red(t_command *node, t_env *envs,
				t_path *path, t_vars vars);
t_env		*full_envs(char **env);
t_env		*new_variable(char *env_key, char *env_value);
char		*get_env_variable(t_env *env, char *env_key);
void		add_env_back(t_env **envs, t_env *new);
void		delete_env(t_env **env, char *env_key);
char		*get_str(char *var, char *type);
void		printstrs(char **map);
void		print_envs(t_env *envs);
char		**expanding_split(char *old_cmd);
int			check_will_splited(t_env *envs, char **cmd, int i);
char		**join_double_with_str(char **s1, char *s2);
char		**join_two_double_strs(char **s1, char **s2);
int			check_is_joinable(char **cmd, int index);
int			ft_check_space_in_cmd(char *str);
char		*double_quotes_p(t_env *envs, char *str, t_path *path, int is_pipe);
char		*single_quotes_process(char *str);
int			is_only_spaces(char *str);
// execution
void		execute(t_command *command, t_env **env_vars, t_path *path);
void		setup_signals(int action);
// heredoc
char		*expanding_herdoc(t_env *envs, char *str, t_path path);
char		*expanding_cmd_herdoc(t_env *envs, char *old_cmd, t_path path);
void		clear_herdocs(t_path *path);
int			handle_herdoc(t_command *command, t_path *path,
				t_env **envs, int input);
t_heredoc	*lst_heredoc_new(char *delimiter, char *file);
void		lst_heredoc_add_back(t_heredoc **lst, t_heredoc *new);
char		*get_right_delimeter(char *s);
int			check_will_expanded(char *delimter);
int			is_any_heredoc(char **red);
// utils
void		exit_status_case(t_vars *vars, t_path *path, int is_pipe);
void		last_command_case(t_vars *vars, t_env *envs);
void		double_quotes_helper(t_env *envs,
				t_vars *vars, t_path *path, char *str);
t_vars		ft_initialize_vars(void);
char		**ft_allocate(int size);
int			skip_spaces(char *str, int index, int *j);
int			check_will_splited_helper3(t_vars vars,
				char **cmd, int i);
int			check_will_splited_helper2(t_env *envs, t_vars vars,
				char **cmd, int i);
void		check_helper2_1(t_env *envs, t_vars *vars, char **cmd, int i);
int			check_will_splited_helper1(t_env *envs, t_vars vars,
				char **cmd, int i);
int			check_will_splited_ambg(t_env *envs, char **cmd, int i);
int			check_will_splited_helper_ambg1(t_env *envs, t_vars vars,
				char **cmd, int i);
void		skip_dollars(char **cmd, int i, int *j, int *nbr);
void		add_dollars(t_vars *vars, int c);
void		add_string(t_vars *vars, char *str);
void		count_dollars(t_vars *vars, char *str);
char		**single_quotes(t_env *envs, t_vars vars, int *index);
t_command	*allocate_node(void);
int			ft_is_red(char *str);
//tty
void		set_up(struct termios *attrs);
void		tty_attributes(struct termios *attrs, int action);
// garbage collector
void		*my_malloc(size_t size, int mode);

#endif