# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejandj <alejandj@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/17 13:58:48 by alejandj          #+#    #+#              #
#    Updated: 2026/01/04 21:31:57 by alejandj         ###   ########.fr        #
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
		src/env_utils_1.c					\
		src/env_utils_2.c					\
		src/prompt.c						\
		src/frees.c							\
		src/mini_utils.c					\
		src/builtins/builtins_main.c		\
		src/builtins/ft_echo.c				\
		src/builtins/ft_cd.c				\
		src/builtins/ft_pwd.c				\
		src/builtins/ft_export.c			\
		src/builtins/ft_unset.c				\
		src/builtins/ft_env.c				\
		src/builtins/ft_exit.c				\
		src/execution/exec_simple_cmd.c		\
		src/execution/redirection.c			\
		src/execution/execution.c			\
		src/parser/count_tokens.c			\
		src/parser/split_tokens.c			\
		src/parser/split_tokens_utils.c		\
		src/parser/calc_expanded_len.c		\
		src/parser/expand_vars.c			\
		src/parser/expand_vars_utils.c		\
		src/parser/validate_line.c			\
		src/parser/create_cmd_list.c		\
		src/parser/remove_quotes.c			\
		src/pipex/here_doc.c				\
		src/pipex/pipex_utils.c				\
		src/pipex/waaaaa.c					\
		src/signals/signals.c

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
