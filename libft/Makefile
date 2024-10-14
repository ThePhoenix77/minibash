NAME		=	libft.a

HEADER		=	libft.h

CFILES		=	ft_bzero.c ft_isalpha.c ft_isalpha.c ft_isalnum.c ft_isascii.c ft_isdigit.c \
          		ft_isprint.c ft_memcpy.c ft_memmove.c ft_memset.c ft_strlen.c ft_substr.c \
          		ft_itoa.c ft_striteri.c ft_putstr_fd.c ft_putnbr_fd.c \
          		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
          		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
          		ft_atoi.c ft_calloc.c ft_strdup.c ft_strjoin.c ft_strmapi.c \
          		ft_putchar_fd.c ft_putendl_fd.c ft_split.c

OFILES		=	$(CFILES:.c=.o)

BONUS_CFILES	=	ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
					ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \

BONUS_OFILES	=	$(BONUS_CFILES:.c=.o)

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror

all:	$(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OFILES)
	@ar rcs $(NAME) $(OFILES)

bonus: $(BONUS_OFILES)
	@ar rcs $(NAME) $(BONUS_OFILES)

clean:
	@rm -rf $(OFILES) $(BONUS_OFILES)

fclean:	clean
	@rm -rf $(NAME)

re:	fclean all

.PHONY:	clean fclean all re bonus