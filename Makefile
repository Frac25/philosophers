NAME = philo

PROG =	philosophers\


SRC = $(addsuffix .c, $(PROG))

OBJ = $(addsuffix .o, $(PROG))

CC = cc

CFLAGS = -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

%.o:		%.c
			$(CC) -c $< $(CFLAGS) -o $@

clean:
			rm -f $(OBJ)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

a:			fclean all clean

.PHONY:		all clean fclean re a
