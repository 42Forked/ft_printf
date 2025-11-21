NAME 	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

SRCS		= ft_printf.c\
			  specifiers/ft_getchar.c\
			  specifiers/ft_getstr.c\
			  specifiers/ft_getptr.c\
			  specifiers/ft_getint.c\
			  specifiers/ft_gethex.c\
			  utils/ft_misc.c\
			  utils/ft_strings.c\
			  utils/ft_parsing.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcu $@ $?

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
