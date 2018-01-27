
NAME = minishell

SRC = count.c env.c main.c utility.c

OBJ = $(SRC:.c=.o)

HEADER = ./minishell.h

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) -I $(HEADER) ../libft/libft.a

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

