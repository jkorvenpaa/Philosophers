NAME = philo
COMPILER = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
SRCS = main.c parser.c utils.c ft_atoi.c dinner.c
	
OBJS = $(SRCS:%.c=%.o)

.SECONDARY:$(OBJS)

all: $(NAME)

$(NAME):$(OBJS)
	$(COMPILER) $(CFLAGS) $(OBJS) -o $(NAME) 

%.o: %.c
	$(COMPILER) $(CFLAGS) -c $< -o $@

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
