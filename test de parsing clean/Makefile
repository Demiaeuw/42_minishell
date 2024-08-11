# Nom de l'exécutable
NAME = minishell

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror

# Sources
SRCS = main.c

# Objets (les fichiers .o)
OBJS = $(SRCS:.c=.o)

# Règle principale
all: $(NAME)

# Création de l'exécutable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

# Compilation des fichiers .c en fichiers .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	rm -f $(OBJS)

# Nettoyage complet (fichiers objets + exécutable)
fclean: clean
	rm -f $(NAME)

# Recompilation complète
re: fclean all

# Règles phony (ces règles ne correspondent pas à des fichiers réels)
.PHONY: all clean fclean re
