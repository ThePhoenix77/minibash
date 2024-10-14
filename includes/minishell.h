/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tboussad <tboussad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 06:57:29 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/10 17:38:00 by tboussad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SUCCESS true
# define FAILURE false
# define HISTORY_FILE "~/.bash_history"
# define META_CHARS " \t\n\'\"><|"

/*~~~~~~~~~~~Syntax Error~~~~~~~~~~~~*/
# define UNCLOSED_QUOTE "minishell: syntax error: unexpected end of file.\n"
# define ERROR "minishell: syntax error near unexpected token `"
# define ERR_MANY_HERDOCS "minishell-1.0$: maximum here-document count \
exceeded\n"
/*~~~~~~~~~~~~~Excution Errors~~~~~~~~~~*/
# define ERR_CMD_NF ": command not found\n"

# include "../libft/libft.h"
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <errno.h>
# include <limits.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "structs.h"
# include <sys/stat.h>

/*~~~~~~~~~~~~~~~~~~~~~signals~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void			init_sigaction(void);
void			signals_handler(int sig);
void			exit_status_update(t_global *global);
void			sig_ign(void);
void			sig_dfl(void);
void			sig_hnd(void);
/*----------------linked list functions--------------*/
void			free_lst(t_lst	**head);
t_lst			*last_node(t_lst *head);
void			add_list(t_global *global);
t_lst			*new_node(t_global *global);
bool			add_back(t_lst **head, t_lst **new);
/*----------------linked env list functions--------------*/
t_env_list		*new_env_node(char *content);
t_env_list		*last_env_node(t_env_list *head);
void			free_env_list(t_env_list **head);
void			add_env_back(t_env_list **head, t_env_list *new);
/*------------------Env functions-----------------------*/
bool			check_env(t_global *global);
bool			empty_env(t_global *global);
bool			shell_level(t_global *global);
t_env_list		*get_var_env(t_global *global, char *var);
bool			update_env(t_env_list **env, char *new_val);
/*----------------utils functions-----------------------*/
int				ft_strcmp(char *s1, char *s2);
void			free_memory(t_global *global);
int				check_valid_in(t_global *global);
int				ft_strlen_un_char(char *str, char c);
int				ft_strlen_un_del(char *sep, char *str);
void			init_global(t_global *global, char **env);
/*~~~~~~~~~~~~~~Tonkenzition functions~~~~~~~~~~~~~~~~*/
void			get_opr(t_global *global);
void			ft_tokeniz(t_global *global);
void			check_type(t_global *global);
void			check_state(t_global *global);
bool			check_syntax(t_global *global);
void			check_here_doc(t_global *global);
bool			check_operator(t_global *global);
bool			check_num_heredoc(t_global *global);
bool			check_heredoc_dred(t_global *global);
void			skip_ec_t(t_global *global, int flag);
void			get_str_inside_quote(t_global *global);
char			*get_word(char **line, int len, t_global *global);
void			update_line(char **line, int len_skip, t_global *global);
/*~~~~~~~~~~~~~~~~~~~~Expanding~~~~~~~~~~~~~~~~~~~~*/
t_expand_list	*new_exp_node(char *content);
t_expand_list	*last_exp_node(t_expand_list *head);
void			join_result(t_global *global);
bool			check_expand(t_global *global);
bool			main_exp_fun(t_global *globol);
void			transform_env(t_global *global);
void			update_var_name(t_global *global);
void			free_exp_list(t_expand_list **head);
bool			split_exp(t_global *global, char **line);
bool			get_exp_var(t_global *global, char **line);
void			finish_exp(t_global *global, t_lst **node);
void			last_step_exp(t_global *global, t_lst *node);
char			*ft_strjoin2(char const *s1, char const *s2);
bool			special_expand(t_global *global);
bool			add_exp_back(t_expand_list **head, t_expand_list *new);
/*~~~~~~~~~~~~~~~~~~~~~here_doc~~~~~~~~~~~~~~~~~~~~~~~~~~*/
bool			check_heredoc(t_global *global);
void			open_heredoc_file(t_global *global);
void			empty_here_doc(t_global *global, t_lst *node);
/*~~~~~~~~~~~~~~~~~~~~~excution~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void			main_exc(t_global *global);
void			add_pre_list(t_global *global);
int				exc_list_size(t_exc_list *exc);
t_exc_list		*last_exc_node(t_exc_list *head);
void			bulid_list_exc(t_global *global);
void			free_exc_list(t_exc_list **head);
int				execute_one_cmd(t_global *global);
void			env_list_2d_array(t_global *global);
void			handle_redir_once(t_global *global);
int				join_cont(t_global *global, t_lst *tmp);
void			split_env(t_global *global, t_lst *tmp);
void			create_node(t_global *global, t_lst **node);
void			add_back_exc(t_exc_list **head, t_exc_list *new);
t_exc_list		*new_exc_spot(t_global *global, t_type_node type);
bool			redir_one_node(t_global *global, t_exc_list **exc_node);
bool			execute_one_builtin(t_global *global,
					char **cmd_args, t_exc_list *exc_node);
/*~~~~~~~~~~~~~~~~~~~~~~BUILTINS~~~~~~~~~~~~~~~~~~~~*/
int				ft_pwd(t_global *global);
void			ft_env(t_global *global);
void			ft_echo(t_global *global, char **args);
size_t			ft_strnlen(char *s, size_t maxlen);
void			ft_export(t_global *global, char **args);
char			*ft_strcpy(char *dest, const char *src);
void			export_without_args(t_global *global);
char			*get_env_value(char *content);
void			update_pwd(t_global *global);
void			change_to_oldpwd(t_global *global);
int				oldpwd_check(t_global *global);
int				is_valid_name_char(char c);
int				name_checker(char *s);
int				arg_size(char **args);
char			*update_the_env_var(t_global *global, char *name, char *new_val);
void			handle_key_value(t_global *global, char *content);
t_env_list		*find_var(t_env_list *env_list, char *key);
int				check_builtins(t_global *global, char **cmd);
void			existing_var_case(t_global *global, char *key);
void			handle_key_value(t_global *global, char *content);
void			add_export_node(t_env_list **head, t_env_list *new);
char			*ft_strndup(char *src, int n);
char			*create_new_content(char *key, char *value);
void			ft_cd(t_global *global, char **args);
void			ft_exit(t_global *global, char **args);
void			ft_unset(t_global *global, char **args);
void			err_msg(char **args);
void			update_env_var(t_env_list *env_var, char *new_content);
void			add_or_update_env_var(t_global *global,
					char *key, char *value, int type);
/*~~~~~~~~~~~~~~~~~~~~~~COMMANED~~~~~~~~~~~~~~~~~~~~~~~~*/
void			cmd_msg(char *cmd);
void			ft_cmd_err(char *cmd);
void			free_cmd_list(t_cmd_args **head);
char			*find_path(char **split, char *cmd);
char			*get_path(char *cmd, t_global *global);
void			check_builtins_cmds(t_exc_list *exc_node);
void			store_cmd_args(t_global *global, t_lst **node);
t_cmd_args		*new_cmd_element(t_global *global, char *content);
void			add_back_element(t_cmd_args **head,
					t_cmd_args *new);
char			**get_args_arr(t_global *global,
					t_cmd_args *cmd_args, t_type_node type);
void			add_list_cmd(t_global *global, t_exc_list *exc, t_lst **node);
/*~~~~~~~~~~~~~~~~~~~~~~redirections~~~~~~~~~~~~~~~~~*/
void			check_redir(t_global *global);
void			free_redir_list(t_redir **head);
void			handle_redir_in(t_redir *redir, t_fd *fds);
t_redir			*new_vertex(t_global *global, t_lst *node);
void			handle_redir_out(t_redir *redir, t_fd *fds);
void			handle_dredir_out(t_redir *redir, t_fd *fds);
void			add_back_redir(t_redir **head, t_redir *new);
void			build_redir_list(t_global *global, t_lst **node);
bool			handle_redirection(t_redir *redir_list, t_fd *fds);
bool			check_doubel_redir(t_global *global, t_redir **redir_list);
/*~~~~~~~~~~~~~~~~~~~~Main Functions~~~~~~~~~~~~~~~~~~~*/
bool			start(t_global *global);
void			get_line(t_global *global);
void			free_2d_array(char ***leaks);
void			malloc_failed(t_global *global);
/*~~~~~~~~~~~~~~~~~~Tree Struct~~~~~~~~~~~~~~~~~~~~~~~*/
int				exit_status(int status, t_global *global);
void			free_tree(t_tree **root);
int				execute_tree(t_global *global, t_tree *root);
t_tree			*build_tree(t_global *global, t_exc_list **old);
int				execute_left(t_global *global, t_tree *root, int *pipe);
int				execute_right(t_global *global, t_tree *root, int *pipe);
int				execute_cmd(t_global *global, char **cmd, t_type_node type);
/*~~~~~~~~~~~~~~~~~~Tty Functions~~~~~~~~~~~~~~~~~~~~~~~*/
void			save_tty(t_global *global);
void			reset_tty(t_global *global);
void			handler(int sig);
/*~~~~~~~~~~~~~~~~~~~Syscall Functions~~~~~~~~~~~~~~~~~~~*/
bool			ft_dup2(int fd1, int fd2);
int				ft_dup(int fd1, int fd2);
bool			ft_close(int fd);
bool			reset_sett(t_fd *fds);
int				close_pipe(int *pipe);

#endif