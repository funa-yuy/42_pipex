# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfunakos <mfunakos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/08 01:21:55 by miyuu             #+#    #+#              #
#    Updated: 2025/02/15 22:42:21 by mfunakos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = #-Wall -Wextra -Werror
NAME = pipex

# Directories
SRC_DIR = ./src
LIBFT_DIR = ./libft

# Source files
SRC_FILES = main.c \
			fill_cmds.c \
			get_cmd_path.c \
			child_process.c \
			execute_cmd.c \
			child_setup_fd.c \
			parent_setup_fd.c \
			utils.c

SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJS = $(SRC:.c=.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
