NAME 	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

SRCS		= ft_printf.c utils/ft_gethex.c utils/ft_getint.c utils/ft_misc.c
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
