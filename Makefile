SRC = src/pipex.c \
	src/ft_split.c \
	src/calloc.c \
	src/command.c \
	src/here_doc.c
CC = gcc
CFLAGS = -Werror -Wall -Wextra
HEADER = pipex.h
NAME = pipex
OBJET = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJET)
	$(CC) $(CFLAGS) $(OBJET) -o $(NAME)

.o : .c
	$(CC) $(CFLAGS) $? -c -o $(OBJET)

clean :
	rm -f $(OBJET)

fclean : clean
	rm -f $(NAME)

save :
	git commit -am autosave
	git push https://github.com/swautelet/pipex.git

re : fclean all

.phony : all $(NAME) clean fclean re