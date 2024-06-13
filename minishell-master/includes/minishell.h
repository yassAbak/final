/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayassaye <ayassaye@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 17:14:31 by ayassaye          #+#    #+#             */
/*   Updated: 2024/06/13 18:23:13 by ayassaye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <limits.h>
# include <signal.h>
# include <dirent.h>

# define BUFFER_SIZE 4096
# define CLOSED 0
# define OPENED 1

typedef enum e_type
{
	S_QUOTE_OPEN,
	S_QUOTE_CLOSE,
	D_QUOTE_OPEN,
	D_QUOTE_CLOSE,
	SL_REDIR,
	SR_REDIR,
	DL_REDIR,
	DR_REDIR,
	PIPE,
	ARGV,
	SPACES
}	t_type;

typedef struct s_fd
{
	int	fd_in;
	int	fd_out;
	int	old_in;
	int	old_out;
}	t_fd;

typedef struct s_env
{
	char			*str;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	t_token			*token;
	pid_t			child_pid;
	struct s_cmd	*next;
	int				fd_in;
	int				fd_out;
}	t_cmd;

typedef struct g_global
{
	int		squote_open;
	int		dquote_open;
	int		exit_value;
	int		shell_level;
	t_token	*token;
	t_env	*env;
	t_cmd	*cmd;
	int		heredoc;
}	t_global;

extern t_global	*g_data;

int			ft_isalnum(char c);
int			ft_isspace(char c);
char		*ft_itoa(int nbr);
void		ft_putstr_fd(char *s, int fd);
char		**ft_split(const char *s, char c);
char		*ft_strjoin_char(char *s1, char c);
char		*ft_strjoin(char *s1, char *s2);
char		*ft_strjoin_no_free(char *s1, char *s2);
int			ft_strlen(const char *s);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strndup(char *str, int len);
char		*ft_strnstr_bis(const char *haystack, const char *needle, int len);
int			ft_isdigit(int c);
int			ft_isdigit_str(char *str);
int			ft_strncmp_bis(char *s1, char s2);
long long	ft_atoi(const char *nptr);
char		*ft_strnstr(const char *big, const char *little, size_t len);

int			is_there_builtin(t_token *token);
int			is_there_redir(t_token *token);
int			is_there_input_redir(t_token *token);
int			is_there_output_redir(t_token *token);
int			is_there_type(t_token *token, t_type type);
int			is_path(char *str);
int			is_successive_pipes(t_token *token);
int			is_opened(char c);
int			how_many(t_token *token, t_type type);
t_type		what_type(char *word, t_type type);
t_token		*create_token(char *word, t_type type);
void		add_token(t_token **token, char *word, t_type type);
int			tokensize(t_token *token, int pipe);
int			ft_envsize(t_env *env);
t_env		*init_env(char **envp);
void		add_env(t_env **env, char *str);
int			is_env(t_env *env, char *str);
t_env		*create_elem_env(char *str);
char		*ft_strcpy_env(char *dest, char *src);
int			ft_strlen_env(char *str);
void		ft_waitpid(pid_t pid);
void		del_elem_env(t_token *arg, t_env *tmp);
int			ft_error(char *str);
void		ft_free_tab(char **tab);
void		free_token(t_token **token);
void		free_env(t_env **env);
void		free_all(int pipeflag);

void		lexer(char *str, t_env *env);
void		lexer_type_handler(char *str, int *i, t_token **token);
char		*lexer_redir_handler(char *str, char *dest, int *i);
char		*lexer_pipe_handler(char *str, char *dest, int *i);
char		*lexer_space_handler(char *str, char *dest, int *i);
char		*lexer_dollar_handler(char *str, char *dest, int *i, t_env *env);
char		*lexer_dquote_handler(char *str, char *dest, int *i);
char		*lexer_squote_handler(char *str, char *dest, int *i);
char		*lexer_char_handler(char *str, char *dest, int *i);
char		*dollar_envp(char *str, char *dest, int *i, t_env *env);
char		*dollar_loop(char *str, int *i, t_env *env);

void		parser(void);
void		parser_quote_handler(t_token *lexed, t_token **token);
void		prepare_token_to_exec(t_token *token);

void		exec_handler(char **envp);
void		ft_exec(char **cmd, char **envp);
char		*getpath(char *cmd, char **envp);
char		**token_to_tab(t_token *token);
char		**tenv_to_tab(t_env *env);
void		close_fds_cmd(t_cmd *cmd);
int			check_parent_builtin(char **args, char **envp, t_cmd **cmd);

void		builtin_handler(t_token *token, int pipeflag);
int			ft_echo(t_token *token);
void		ft_pwd(void);
void		ft_env(t_env *env);
void		ft_exit(t_token *token, int pipeflag);
int			ft_cd(t_token *token, t_env *env);
int			ft_export(t_token *token, t_env *env);
void		ft_unset(t_token *token);
int			pwd_change(t_env *env);;
int			oldpwd_change(t_env *env);
char		*get_path(t_env *env, char *location, size_t len);
int			change_path(t_env *env, char *s1, char *s2, int lencmp);
int			not_alnum(char *to_search);
int			check_arg(char *str);
int			find_char(char *s1, char c);
int			handle_no_param(t_env *env);
int			count_arg(t_token *token);
void		change_level(t_env *env);
int			find_char(char *s1, char c);
int			is_valid_builtin(char *target, char *str, int allchar);
int			error_export(t_token *arg);
void		printf_err(char *s1, char *s2, char *arg);
void		printf_err_strerror(char *cmd, char *str);
void		builtin_handler_parent(t_token *token);

void		signal_interactive(int sig);
void		signal_no_interactive(int sig);
void		ctrl_d_handler(char *buff);
void		signal_heredoc(int sig);

void		pipe_exec(char **envp);
int			pipe_error_handler(void);
t_token		*token_to_token(t_token *token, int nb_pipe);
t_cmd		**add_cmd(t_cmd **cmd);
void		set_fd_pipes(t_cmd **cmd);
void		token_to_cmd(t_cmd **cmd);
void		free_cmd(t_cmd **cmd);
void		dup_all_fd(t_cmd *cmd);

int			create_tmp_heredoc(t_token *token, int fd);
t_token		*new_exec_token(t_token *old);
int			in_out_error(t_token *token);
int			existing_file_in(t_token *token, int fd);
int			existing_file_out(t_token *token, int fd, t_type type);
int			files_handler(t_cmd *cmd, t_token *token);
void		set_fd_redir(t_cmd **cmd);

#endif