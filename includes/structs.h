/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaboudi <eaboudi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:31:37 by eaboudi           #+#    #+#             */
/*   Updated: 2024/10/05 16:51:53 by eaboudi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

extern int					g_exit_status;
typedef struct sigaction	t_sigaction;

typedef enum e_type
{
	WORD = 1,
	REDIR_OUT = 2,
	REDIR_IN = 3,
	HERE_DOC = 4,
	DREDIR_OUT = 5,
	PIPE = 6,
	WHITE_SPACE = 7,
	DOUBLE_QUOTE = 8,
	ENV = 10,
	NEW_LINE = 11,
	TABS = 12,
	SINGEL_QOUTE = 13,
	EMPTY_ENV = 14,
	ENV_SPL = 15,
	EXP_HERE_DOC = 16,
	HERE_DOC_FILE = 17,
	ERROR_DIS = 18,
	SKIP = 19,
}	t_type;

typedef enum e_env_type
{
	SHOW,
	HIDE,
}	t_env_type;

typedef enum e_state
{
	GENERAL,
	IN_DQUOTE,
	IN_SQUOTE,
}	t_state;

typedef struct s_lst
{
	char			*content;
	struct s_lst	*next;
	struct s_lst	*prev;
	t_state			state;
	t_type			type;
	int				len;
}	t_lst;

typedef struct s_env_list
{
	char				*content;
	struct s_env_list	*next;
	struct s_env_list	*prev;
	int					type;
}	t_env_list;

typedef struct s_expand_list
{
	char					*content;
	struct s_expand_list	*next;
	struct s_expand_list	*prev;
	t_type					type;
}	t_expand_list;

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef enum e_file_type
{
	OUT = 2,
	IN = 3,
	DOUT = 5,
	HRDC = 17,
	ERR_DIS = 18,
}	t_file_type;

typedef struct e_redir
{
	struct e_redir	*next;
	char			*file_name;
	t_type			file_type;
	t_type			type;
}	t_redir;

typedef struct s_cmd_args
{
	char				*content;
	struct s_cmd_args	*next;
}	t_cmd_args;

typedef enum e_type_node
{
	PIPE_LINE,
	CMD,
	BUILTIN,
}	t_type_node;

typedef struct s_exc_list
{
	t_fd				fd;
	t_type_node			type;
	struct s_exc_list	*next;
	t_redir				*redir;
	t_cmd_args			*cmd_args;
}	t_exc_list;

typedef struct s_tree
{
	t_fd			fds;
	t_type_node		type;
	struct s_tree	*left;
	t_redir			*redir;
	struct s_tree	*right;
	char			**cmd_args;
}	t_tree;

typedef struct s_global
{
	char			*line_input;
	char			*content;
	int				list_len;
	char			**env;
	char			**myenv;
	t_exc_list		*root;
	t_lst			*head;
	t_lst			*pre_head;
	t_lst			*tmp;
	t_env_list		*env_list;
	t_expand_list	*exp_head;
	t_tree			*root_tree;
	int				state;
	int				type;
	int				exit_status;
	int				here_doc_num;
	int				exc_size;
	t_fd			save_fd;
	int				pipe[2];
	struct termios	t_termios;
}	t_global;

#endif