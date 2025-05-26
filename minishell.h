/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouerchi <mouerchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 23:55:26 by azaimi            #+#    #+#             */
/*   Updated: 2025/05/26 22:07:06 by mouerchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <errno.h>
# include <sys/wait.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/ioctl.h>

extern int	g_global_her;

typedef struct s_her
{
	int		fd;
	int		val;
	int		flag;
	int		fd_beg;
	int		count_per;
	char	*temp;
	char	*check;
	char	*rl_her;
	char	*name;
}	t_her;

typedef struct s_dec
{
	char	*buff;
	char	*temp;
	char	quote;
}	t_dec;

typedef struct s_exp
{
	int			j;
	int			flag;
	int			count;
	char		*res;
	char		*temp;
	char		*name;
	char		*temp_res;
	char		*temp_var;
	char		*temp_val;
}	t_exp;

typedef struct s_h_w
{
	int		j;
	int		q;
	int		flag;
	char	*buff;
	char	*temp;
	char	**temp_2;
}	t_h_w;

typedef enum e_token
{
	T_WORD,
	T_RED,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HERDOC,
	T_SIGN,
	T_SQUOTE,
	T_DQUOTE,
}	t_token_type;

typedef enum e_quotes
{
	NONE,
	S_QUOTES,
	D_QUOTES,
}	t_quotes_state;

typedef enum e_loop
{
	BREAK,
	CONTINUE,
}	t_state_loop;

typedef enum e_error
{
	ERR_NONE,
	ERR_SYNTAX,
	ERR_NO_FILE,
	ERR_NUM_ARG,
	ERR_TOO_MANY_ARGS,
	ERR_INVALID_OPTION,
	ERR_UNCLOSED_QUOTES,
	ERR_PERMISSION_DENIED,
}	t_error_type;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_q
{
	int	single_q;
	int	double_q;
}	t_q;

typedef struct s_pid
{
	pid_t			pid;
	struct s_pid	*next;
}	t_pid;

typedef struct s_name
{
	int				fd;
	struct s_name	*next;
}	t_name;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	char			*exp;
	struct s_token	*next;
}	t_token;

typedef struct s_files
{
	char			*name;
	char			*type;
	struct s_files	*next;
}	t_files;

typedef struct s_parse
{
	char			*cmd_name;
	char			**args;
	t_files			*file;
	int				builtins;
	int				infile;
	int				outfile;
	int				file_fail;
	struct s_parse	*next;
}	t_parse;

typedef struct s_env
{
	char			*variable;
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_config
{
	t_parse	*cmd;
	t_env	*env_lst;
	t_name	*her_name;
	t_pid	*pids;
	int		exp;
	char	**env;
	bool	fail;
	int		flag_c;
	bool	env_exist;
	int		saved_fd;
	int		pipe[2];
	int		cmd_idx;
	char	*path;
	int		amb;
	int		std_in;
	int		std_out;
	int		child_flag;
	int		isexpanded;
}	t_config;

int				is_numeric(char *str);
char			*ft_handle_words(char *rl, int i);
void			ft_handle_redir_out(char *rl, int *i, t_token **lst);
void			ft_handle_redir_in(char *rl, int *i, t_token **lst);
void			ft_handle_word(char *rl, int *i, t_token **lst, \
	t_config *config);
char			*ft_strjoin(char *s1, char *s2);
void			ft_free_token_list(t_token *lst);
int				count_words_before_pipe(t_token *token);
char			*ft_strjoin_char(char *s1, char c);
void			ft_lstadd_back_files(t_parse **lst, t_files *new);
t_files			*ft_files_new(char *name, char *type);
int				ft_strcmp(char *str1, char *str2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
t_token			*ft_token_new(t_token_type type, \
	void *content, void *content_2);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
t_token			*ft_lstlast_token(t_token *lst);
t_parse			*ft_parsing(t_token **token, t_config *config);
t_parse			*ft_parse_new(void);
char			*ft_strdup(char *s);
t_token			*ft_add_cmd(char *rl, t_config *config);
t_parse			*parse_piped_commands(t_token **token_p, t_config *config);
char			**ft_check_parse(t_token **check, t_config **config, int *i);
int				ft_lstsize_token(t_token *token);
void			ft_builtins_check(t_parse *par);
int				f_strcmp(const char *s1, const char *s2);
t_quotes_state	ft_handle_quotes(char *rl);
t_error_type	ft_handle_error(char *rl);
void			ft_print_list(t_parse *cmd);
size_t			ft_strlen(char *str);
char			*ft_strtrim(char *s1, char *set);
void			ft_print_list_2(t_token *cmd);
char			*ft_strchr(char *s, int c);
char			*ft_strcpy(char *dest, char *src);
char			*ft_substr(char *s, unsigned int start, size_t len);
void			handle_redirection(t_token **check, t_parse **p);
void			process_char(char *rl, int *i, t_token **lst, t_config *config);
char			*ft_handle_buff(char *rl, int *i);
void			init_env(t_config *config, char **env);
char			*trim_free(char *str);
char			*ft_getenv(char **env, char *env_name);
char			**get_env(char **real_env);
int				fail_check(char ***env, int i);
t_env			*get_env_lst(t_config *config);
void			append_env_lst(t_env **lst, char *variable);
void			free_lst(t_env **lst);
void			free_env_lst(t_env *env);
char			**ft_split_var(char *variable);
char			*ft_itoa(int n);
long long		ft_atoi(const char *str, bool *flag);
char			*ft_search_lst(t_config *config, char *buff);
int				is_numeric_char(char *str, int i);
int				is_alpha_char(char *str, int i);
int				ft_isalnum(int ch);
int				ft_isdigit(int ch);
int				ft_isalpha(int ch);
char			*ft_strjoin_free(char *s1, char *s2);
void			*ft_memcpy(void *dest, const void *src, size_t n);
char			*ft_handle_name(char *buff, int *i);
int				ft_calc_dol(char *buff, int i);
void			ft_quotes_exp(char *buff, int *i, t_q *quotes);
char			*merge_temp(char *buff, int *i, char *temp, t_q *quotes);
char			**ft_split(char *s, char *delims);
size_t			ft_strlcpy(char *dst, char *src, size_t dstsize);
void			execute_cmd(t_config *config, t_parse *cmd);
int				ft_herdoc(t_config *config, t_token *token, int *flag);
int				handle_char(t_dec *dec, char *rl, int *i);
int				execution(t_config *config);
void			execute_cmd(t_config *config, t_parse *cmd);
int				spawn_child_process(t_config *config, t_parse *cmd);
int				run_builtins(t_config *config, t_parse *cmd);
int				run_builtins_rest(t_config *config, t_parse *cmd);
void			check_env(t_config *config);
void			update_env_array(t_config *config);
void			free_array(char **arr);
char			**lst_to_array(t_env *env_lst);
int				ft_exit(char **arg, int child_flag);
int				ft_unset(t_config *config, char **args);
int				ft_pwd(t_config *config);
int				ft_env(t_env *env_lst);
int				ft_echo(char *str);
int				ft_find_her(t_token *token);
int				validate_pipes_her(t_token *token, t_her *her);
char			*ft_word(char *buff, t_config *config, int *flag);
int				has_doll(char *str);
char			*ft_strchr_q(char *s, int c, int c_2);
int				has_q(char *str);
char			*ft_handle_name_her(char *buff, int *i);
char			*ft_queen(char *buff, t_config *config, t_exp exp, t_q q);
char			*second(char *buff, t_exp exp, int *j, t_q *quotes);
char			*third(char *buff, t_config *config, t_exp exp, int *j);
void			init_queen(t_exp *exp, t_q *quotes);
int				has_doll_2(char *str);
int				ft_if(t_token *token);
void			ft_setenv(t_config *config, char *name, char *value);
int				redir_in(t_parse *cmd, char *file_name);
int				redir_out(t_parse *cmd, char *file_name);
int				redir_append(t_parse *cmd, char *file_name);
char			*array_join(char **str);
void			parent(t_config *config);
void			init_process(t_config *config);
int				ft_cmd_nmbr(t_parse *cmd_lst);
void			run_child_process(t_config *config, t_parse *cmd);
int				check_toprint(char *str, int *i);
void			safe_close(int *fd);
int				extra_her(t_token *token, t_her *her);
void			ft_handle_word_2(t_token **lst, t_config *config, t_h_w *h_w);
int				ft_strcmp_her(const char *s1, const char *s2);
void			msg_error(char *msg1, char *full, char *msg2);
int				is_directory(char *str);
int				is_file(char *str);
int				is_path(char *str);
char			*find_path(char *cmd_name, char **env);
int				ft_export(t_config *config, char **args);
t_name			*ft_name_new(int name);
void			ft_lstadd_back_name(t_name **name, t_name *new);
int				has_q_in_doll(char *buff);
char			*ft_gen_name_file(void);
void			ft_print_list_3(t_name *name);
void			ft_free_name_list(t_name *name);
int				ft_herdoc_3(t_token *token, t_config *config, \
	t_her *her, t_name **name);
int				validate_pipes(t_token *token, t_config *config, \
	int flag, int expect_command);
int				func_1(t_token *token, t_config *config, int *flag);
int				func_2(t_token *token);
int				func_3(t_token *token, int *expect_command);
int				func_4(t_token *token, int *flag);
int				func_5(t_token *token);
int				func_6(char *buff, t_q *q, t_exp *exp);
int				func_7(char *buff, t_q *q, t_exp *exp);
int				is_valid_char(char c);
int				valid_var_name(char *name, char *full);
int				split_var(char *arg, char **name, char **value);
int				exit_status(int status, int rtrn);
void			error_handling(int flag, char *cmd, char *msg, int i);
int				valid_var_name(char *name, char *full);
int				is_valid_char(char c);
int				split_var(char *arg, char **name, char **value);
int				check_cmd_name(char *name);
void			ft_dup(int fd, int redir);
void			ft_close(int fd);
void			restore_redir(t_config *config);
int				open_files(t_name *her_name, t_parse *head_cmd);
int				open_files_utils(t_name **her_name, t_parse *cmd, \
	t_files *file);
void			apply_redir(t_parse *cmd);
int				handel_her(t_parse *cmd, int fd);
int				func_6_her(char *buff, t_exp *exp);
void			init_her(t_exp *exp);
void			sig_int_handle(int sig);
int				ft_cd(char *path, char **env, int *cd_broken);
void			minishell_loop(t_config config, t_token *token, char *rl);
void			free_env_node(t_env *env);
void			free_env_lst(t_env *env);
void			free_lst(t_env **lst);
void			free_files(t_files *files);
char			*ft_handle_words_her(char *rl);
void			free_utils(t_config *config);
void			*pid_new(pid_t pid);
void			lst_add_back_pid(t_pid **head, pid_t pid);
void			free_pids(t_pid **head);
void			free_parse(t_parse **cmd);
void			sig_parent_handler(int sig);
void			sig_handler_her(int sig);
void			ft_re_init_her(t_config *config);
char			*ft_strjoin_2(char *s1, char *s2);
int				check_option(char **args);
void			option_error(char *cmd, char *option);
int				run_builtins_rest_2(t_config *config, t_parse *cmd);
int				ft_update_pwd(t_config *config);
void			ft_update_pwd_fail(t_config *config, char *arg);
void			env_error_arg(char *cmd, char *arg);
void			ft_signal(void);
void			ft_free_utils_2(t_config config, t_token *token, char *rl);
void			ft_free_utils_3(t_token *token, char *rl);
void			do_split_var(char ***var_array, char *env);
void			sort_env_2(char **sorted_env, int count);
void			sort_env(char ***env, char ***sorted_env);
int				empty_rl(char *rl);
void			ft_strcpy_join(char *dst, char *s1, char *s2);
int				ft_isspace(char *rl);
void			update_shlvl(size_t *shlvl);

#endif