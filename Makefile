# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/17 13:58:48 by alejandj          #+#    #+#              #
#    Updated: 2025/11/28 12:33:12 by alejandj         ###   ########.fr        #
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
		src/mini_utils_1.c					\
		src/mini_utils_2.c					\
		src/execution.c						\
		src/builtins/builtins_main.c		\
		src/builtins/ft_echo.c				\
		src/builtins/ft_cd.c				\
		src/builtins/ft_pwd.c				\
		src/builtins/export/ft_export.c		\
		src/builtins/export/export_utils.c	\
		src/builtins/export/parse.c			\
		src/builtins/ft_unset.c				\
		src/builtins/ft_env.c				\
		src/builtins/ft_exit.c				\
		src/parser/parser_pipex.c			\
		src/parser/parser_pipex_utils.c		\
		src/parser/split_tokens.c			\
		src/parser/expand_vars.c			\
		src/parser/calc_expanded_len.c		\
		src/parser/expand_vars_utils.c	\
		src/pipex/main_bonus.c				\
		src/pipex/pipex_extra_bonus.c		\
		src/pipex/pipex_heredoc_bonus.c		\
		src/pipex/pipex_utils_bonus.c		\
		src/pipex/waaaaa.c					\
		src/pipex/pipex_minishell.c			\
		src/pipex/pipex_minishell_utils.c

OBJECTS = $(SRC:src/%.c=$(OBJDIR)/%.o)

# Library
LIBFT = $(LIBDIR)libft.a

all: $(NAME)

# ---------------------------------------------------------------------------- #
# 💥 RULES
# ---------------------------------------------------------------------------- #

# Create final executable
$(NAME): $(OBJECTS) $(LIBFT)
	@echo ""
	@echo "\033[0;31m⚙️  COMPILANDO... 🚀\033[0m"
	$(CC) $(CFLAGS) $(OBJECTS) -L$(LIBDIR) -lft -lreadline -o $(NAME)
	@echo ""
	@echo "✅ \033[0;32mMINISHELL COMPILADA!!!\033[0m"
	@echo ""

# Compile libft
$(LIBFT):
	@$(MAKE) -C $(LIBDIR) all

# Rule to compile every .c to .o, creating subfolders in obj/ as needed
$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# ---------------------------------------------------------------------------- #
# 🧹 CLEANING
# ---------------------------------------------------------------------------- #
clean:
	@$(MAKE) -C $(LIBDIR) clean
	@rm -rf $(OBJDIR)
	@echo "🧹 \033[0;32mObject files removed successfully! 🗑️\033[0m"

fclean: clean
	@$(MAKE) -C $(LIBDIR) fclean
	@rm -f $(NAME)
	@echo "🚀 \033[0;32mExecutable $(NAME) has been removed! 👋\033[0m"

re: fclean all

.PHONY: all clean fclean re
