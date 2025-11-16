NAME 	= libftprintf.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

SRCS		= ft_printf.c
OBJS		= $(SRCS:.c=.o)

BONUS_SRCS	= ft_printf.c
BONUS_OBJS	= $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcu $@ $?

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcu $(NAME) $?

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
