NAME = pipex

NAME_B = pipex_bonus

SRC = pipex.c ft_split.c pipe_utils.c str_utils.c \
		frite.c invalid.c execute.c

B_SRC = bonus/pipex_bonus.c bonus/bonus_utils.c bonus/free_write.c\
		 bonus/multiple_pipes.c bonus/b_split.c bonus/b_str_utils.c\
		 bonus/here_doc.c bonus/get_next_line.c bonus/invalid.c\

OBJ = $(SRC:.c=.o)

B_OBJ = $(B_SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra

DEL = rm -rf

all: $(NAME)
$(NAME): $(OBJ)
	 $(CC) $(CFLAGS) $^ -o $@

bonus: $(NAME_B)


$(NAME_B): $(B_OBJ)
		$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(DEL) $(OBJ) $(B_OBJ)

fclean: clean
	$(DEL) $(NAME) $(NAME_B)

re: fclean all

rebonus: fclean bonus

.PHONY: all bonus clean fclean re