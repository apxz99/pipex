# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sarayapa <sarayapa@student.42bangkok.co    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/19 08:50:18 by sarayapa          #+#    #+#              #
#    Updated: 2026/01/23 13:59:01 by sarayapa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror

FILES = pipex.c ft_strlen.c ft_split.c ft_strjoin.c \
		ft_strncmp.c ft_calloc.c ft_bzero.c ft_memset.c \
		pipex_utils.c ft_putstr_fd.c ft_strrchr.c ft_strdup.c

SRCS = srcs/
BUILD = builds/
INC = -I .

SRCS_O = $(addprefix $(BUILD), $(FILES:.c=.o))

all: $(BUILD) $(NAME)

$(BUILD):
	mkdir -p $(BUILD)

$(BUILD)%.o: $(SRCS)%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(NAME): $(SRCS_O)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re