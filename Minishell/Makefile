# Nom de l'executable
NAME = minishell

# Dossiers des bibliothèques
LIBFT_DIR = include/utils/libft/
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_INC = -I$(LIBFT_DIR)

FT_PRINTF_DIR = include/utils/ft_printf/
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
FT_PRINTF_INC = -I$(FT_PRINTF_DIR)/includes

GNL_DIR = include/utils/gnl/
GNL = $(GNL_DIR)/libgnl.a
GNL_INC = -I$(GNL_DIR)

# Dossier des fichiers objets
OBJDIR = obj

# Fichiers source
SRCS = 	srcs/main.c\
		srcs/exec/00_error.c\
		srcs/parsing/00_error.c\
		srcs/parsing/01_init.c\
		srcs/parsing/02_free.c\
		srcs/parsing/03_printing.c\
		srcs/parsing/10_parsing.c\
		srcs/parsing/11_token_comp.c\
		srcs/parsing/20_expanser.c\
		srcs/parsing/21_relativ_to_absolute.c\
		srcs/envp/envp.c\
		srcs/envp/envp_utils.c\
		srcs/envp/envp_utils2.c

# Fichiers objets
OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

# Flags de compilation
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g $(LIBFT_INC) $(FT_PRINTF_INC) $(GNL_INC)
RM = rm -rf

# Règle par défaut
all: printhader printactionlibft $(LIBFT) printactionlibftok printactionftprintf $(FT_PRINTF) printactionftprintflok printactiongnl $(GNL) printactiongnlok printactionobj $(NAME) printactionobjok printend

# Règle rapide sans affichage
rapide: $(LIBFT) $(FT_PRINTF) $(GNL) $(NAME) printactionobjokrapide

# Règle pour créer l'exécutable
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(FT_PRINTF) $(GNL)

# Compilation des fichiers objets
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Compilation de la libft
$(LIBFT):
	@$(MAKE) -s -C $(LIBFT_DIR)

# Compilation de ft_printf
$(FT_PRINTF):
	@$(MAKE) -s -C $(FT_PRINTF_DIR)

# Compilation de GNL
$(GNL):
	@$(MAKE) -s -C $(GNL_DIR)

# Règle pour nettoyer les fichiers objets et les bibliothèques
exe: all clean

clean:
	@$(RM) $(OBJDIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(FT_PRINTF_DIR) clean
	@$(MAKE) -s -C $(GNL_DIR) clean

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(FT_PRINTF_DIR) fclean
	@$(MAKE) -s -C $(GNL_DIR) fclean
	@$(MAKE) -s printendclean

re: fclean all

#----------------------------------------------------------------------------

# Règle d'affichage
printhader:
	@sleep 0.1
	@echo "                                                   "
	@sleep 0.1
	@echo "\033[94m _______________________________________ \033[0m"
	@sleep 0.1
	@echo "\033[94m|_______________________________________|\033[0m"
	@sleep 0.1
	@echo "                                         "
	@sleep 0.1
	@echo "  __  __ _       _  _____ _          _ _ "
	@sleep 0.1
	@echo " |  \/  (_)     (_)/ ____| |        | | |"
	@sleep 0.1
	@echo " | \  / |_ _ __  _| (___ | |__   ___| | |"
	@sleep 0.1
	@echo " | |\/| | | '_ \| |\___ \| '_ \ / _ \ | |"
	@sleep 0.1
	@echo " | |  | | | | | | |____) | | | |  __/ | |"
	@sleep 0.1
	@echo " |_|  |_|_|_| |_|_|_____/|_| |_|\___|_|_|"
	@sleep 0.1
	@echo "                                         "
	@sleep 0.1
	@echo "\033[94m _______________________________________ \033[0m"
	@sleep 0.1
	@echo "\033[94m|_______________________________________|\033[0m"
	@sleep 0.1
	@echo "\033[97m                                                   \033[0m"
	@sleep 1

printactionobj:
	@echo " "
	@echo " "
	@sleep 0.5
	@echo "\033[97m   Compilation des\033[0m \033[38;5;208mfichiers OBJET\033[0m --> 💻"
	@echo " "
	@echo " "
	@sleep 0.5

printactionobjok:
	@echo "   Compilation des \033[32mfichiers OBJET\033[0m --> ✅"
	@echo " "
	@echo " "
	@sleep 0.5

printactionobjokrapide:
	@echo " "
	@echo "   Compilation des \033[32mfichiers OBJET\033[0m --> ✅"
	@echo " "

printactionlibft:
	@echo " "
	@echo " "
	@sleep 0.5
	@echo "\033[97m   Compilation de\033[0m \033[38;5;208mLibft\033[0m --> 📚"
	@echo " "
	@echo " "
	@sleep 0.5

printactionlibftok:
	@echo "   Compilation de \033[32mLibft\033[0m --> ✅"
	@echo " "
	@echo " "
	@sleep 0.5

printactionftprintf:
	@echo " "
	@echo " "
	@sleep 0.5
	@echo "\033[97m   Compilation de\033[0m \033[38;5;208mft_printf\033[0m --> 📚"
	@echo " "
	@echo " "
	@sleep 0.5

printactionftprintflok:
	@echo "   Compilation de \033[32mft_printf\033[0m --> ✅"
	@echo " "
	@echo " "
	@sleep 0.5

printactiongnl:
	@echo " "
	@echo " "
	@sleep 0.5
	@echo "\033[97m   Compilation de\033[0m \033[38;5;208mGNL\033[0m --> 📚"
	@echo " "
	@echo " "
	@sleep 0.5

printactiongnlok:
	@echo "   Compilation de \033[32mGNL\033[0m --> ✅"
	@echo " "
	@echo " "
	@sleep 0.5

printend:
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@echo "\033[94m ________________________________________ \033[0m"
	@sleep 0.1
	@echo "\033[94m|________________________________________|\033[0m"
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@echo "   Utilitaire : \033[94m./minishell\033[0m est utilisable."
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@echo "\033[94m ________________________________________ \033[0m"
	@sleep 0.1
	@echo "\033[94m|________________________________________|\033[0m"
	@sleep 0.1
	@echo " "
	@sleep 0.1

printendclean:
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@sleep 0.1
	@echo "\033[94m ________________________________________ \033[0m"
	@sleep 0.1
	@echo "\033[94m|________________________________________|\033[0m"
	@echo " "
	@sleep 0.1
	@echo "   Tous les fichiers sont supprimé 🚮"
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@echo "\033[94m ________________________________________ \033[0m"
	@sleep 0.1
	@echo "\033[94m|________________________________________|\033[0m"
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@echo "   \033[32mMerci d'avoir utilisé\033[0m \033[94mminishell\033[0m"
	@sleep 0.1
	@echo " "
	@sleep 0.1
	@echo "\033[94m ________________________________________ \033[0m"
	@sleep 0.1
	@echo "\033[94m|________________________________________|\033[0m"
	@sleep 0.1
	@echo " "
	@sleep 0.1
