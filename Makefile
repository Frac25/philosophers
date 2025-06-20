NAME = philo

PROG =	act\
		close\
		die\
		lib1\
		lock\
		philo\

OBJ_DIR = obj

SRC = $(addsuffix .c, $(PROG))

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(PROG)))

CC = cc

#CFLAGS =  -Wall -Wextra -Werror
CFLAGS =  -Wall -Wextra -Werror -fsanitize=thread -g
#CFLAGS =  -Wall -Wextra

all:			$(OBJ_DIR) $(NAME)

$(OBJ_DIR):
				mkdir -p $(OBJ_DIR)

$(NAME):		$(OBJ)
				$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

$(OBJ_DIR)/%.o:	%.c
				$(CC) -c $< $(CFLAGS) -o $@

clean:
				rm -f $(OBJ)

fclean:			clean
				rm -f $(NAME)

re:				fclean all

a:				fclean all clean

.PHONY:			all clean fclean re a
