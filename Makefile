CC = cc

NAME = minishell

READLINE_L = ~/.brew/opt/readline/lib
READLINE_I = ~/.brew/opt/readline/include

HEADER = includes

CFILES = builtins/builtins_utils.c builtins/builtins_utils2.c \
         builtins/builtins_utils3.c builtins/builtins_utils4.c \
         builtins/ft_cd.c builtins/ft_echo.c \
         builtins/ft_env.c builtins/ft_exit.c builtins/ft_export.c \
         builtins/ft_pwd.c builtins/ft_unset.c \
         env/env_utils.c env/env_utils2.c env/env_utils3.c \
         env/shell_level.c \
         excution/build_tree.c excution/check_multi_redir.c \
         excution/cmd_list.c excution/exc_list_utils.c excution/exc_utils.c \
         excution/exc_utils2.c excution/execute_cmd.c excution/execute_left.c \
         excution/execute_one_cmd.c excution/execute_right.c \
         excution/execute_tree.c excution/exit_status.c \
         excution/main_exc.c excution/one_cmd_utils.c \
         excution/path_finder.c excution/prepare_exc_list.c \
         excution/redir_handle.c excution/redir_list.c \
         excution/syscall_fun.c \
         expanding/check_node_expn.c expanding/exp_utils.c \
         expanding/exp_utils2.c expanding/ft_expand.c \
         expanding/last_step_exp.c expanding/list_exp_fun.c \
         main.c utils/ft_tokeniz.c \
         Utils/check_redir.c Utils/check_syntax.c Utils/clean_memory.c \
         Utils/ft_heredoc.c Utils/here_doc_utils.c \
         Utils/linked_list_fun.c Utils/signals.c Utils/tty_handler.c \
         Utils/utils.c Utils/Utils_Tokeniz1.c Utils/Utils_Tokeniz2.c

OFILES = $(CFILES:%.c=%.o)

LIBFT_DIR = libft
#
LIBFT = $(LIBFT_DIR)/libft.a

RM = rm -rf

CC += -Wall -Werror -Wextra

all: $(NAME)

#
$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(OFILES) -L $(LIBFT_DIR) -L $(READLINE_L) -lft -lreadline -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) -I $(HEADER) -I $(READLINE_I) -c $< -o $@

clean:
	make clean -C $(LIBFT_DIR)
	$(RM) -rf $(OFILES)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) -rf $(NAME)

re: fclean all
