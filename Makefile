# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/17 13:58:48 by alejandj          #+#    #+#              #
#    Updated: 2025/10/31 17:50:11 by alejandj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable name
NAME = minishell

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iincludes

# Directories
LIBDIR = libft/
OBJDIR = obj/

SRC =	src/main.c							\
		src/mini_utils.c					\
		src/mini_functions.c				\
		src/pipex/main_bonus.c				\
		src/pipex/minishell_compatible.c	\
		src/pipex/pipex_extra_bonus.c		\
		src/pipex/pipex_heredoc_bonus.c		\
		src/pipex/pipex_utils_bonus.c		

OBJECTS = $(SRC:src/%.c=$(OBJDIR)/%.o)

# Library
LIBFT = $(LIBDIR)libft.a

all: $(NAME)

# Make executable
$(NAME) : $(OBJECTS) $(LIBFT)
	@echo ""
	@echo "\033[0;31m⚙️ COMPILANDO... 🚀\033[0m"
	@echo ""
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIBDIR) -lft -lreadline -o $(NAME)
	@echo ""
	@echo "✅ \033[0;32mMINISHELL COMPILADA!!!\033[0m"
	@echo ""

# Compile libft
$(LIBFT):
	@$(MAKE) -C $(LIBDIR) all

# Rule create .o in the directory obj
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object and mode markers
clean:
	@$(MAKE) -C $(LIBDIR) clean
	rm -rf $(OBJECTS)
	@echo "🧹 \033[0;32mObject files removed successfully! 🗑️\033[0m"

# Full clean
fclean: clean
	@$(MAKE) -C $(LIBDIR) fclean
	rm -rf $(NAME)
	@echo "🚀 \033[0;32mExecutable $(NAME) has been removed! 👋\033[0m"

# Rebuild everything
re: fclean all

.PHONY: all clean fclean re