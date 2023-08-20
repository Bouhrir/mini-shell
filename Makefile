# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: obouhrir <obouhrir@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 19:44:36 by obouhrir          #+#    #+#              #
#    Updated: 2023/06/20 20:03:23 by obouhrir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    = minishell
CC      = cc
CFLAGS  = -Wall -Werror -Wextra #-fsanitize=address -g
RDFLAGS = -lreadline #-lhistory
LDFLAGS= -L /goinfre/obouhrir/homebrew/opt/readline/lib
CPPFLAGS= -I/goinfre/obouhrir/homebrew/opt/readline/include/
SRC     = mini.c parse.c parse1.c error.c help.c  alloc_free.c lexer.c shell.c \
		  commands.c expasion.c redirections.c environment.c export.c export_utils.c \
			export_utils2.c shlvl.c search.c s_utils.c builtin_checks.c cd.c cd_utils.c \
			echo.c exit.c unset.c pwd.c
OBJDIR  = objects
OBJ     = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))
LIBFT   = ./libft/libft.a

# Colours
GREEN   = "\033[32m"
GREY    = "\033[30m"
RED     = "\033[31m"

.SILENT:
# Compile all
all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT) $(PRINTF)
	@echo $(GREEN)"Compiling $(NAME)..."
	@$(CC) $(RDFLAGS)  $(CFLAGS) $(OBJ) help1.c $(LIBFT) -o $(NAME)
	@echo "Successfully compiled $(NAME)!"

# Compile object files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	# @echo $(GREY)"Compiling $<..." 
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@echo "Building LIBFT..."
	@make -C libft

# Clean up
clean :
	@echo $(GREY)"Cleaning up..."
	@make -C libft clean
	@rm -rf $(OBJDIR)

fclean : clean
	@echo $(RED)"Removing $(NAME)..."
	@make -C libft fclean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
