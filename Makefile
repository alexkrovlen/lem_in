#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcolossu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/11 20:49:09 by jojoseph          #+#    #+#              #
#    Updated: 2020/05/21 19:42:55 by jojoseph         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = lem_in

ifndef VERBOSE
MAKEFLAGS += --no-print-directory
endif

### PATH ###
SRCS_PATH = src/
OBJ_PATH  = obj/
#LIBFT_PATH = libft/

LIBFT = $(LIBFT_DIRECTORY)libft.a
LIBFT_DIRECTORY = ./libft/
LIBFT_HEADERS = $(LIBFT_DIRECTORY)includes/

HEADERS_LIST = lem_in.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

FLAGS = -Wall -Werror -Wextra
INC = -I $(HEADERS_DIRECTORY) -I $(LIBFT_HEADERS)

SRCS_NAME = parse.c \
			init_rooms.c \
			error.c \
			maps.c \
			free.c \
			room.c \
			help.c \
			print.c \
			algo.c \
			algo_bfs.c \
			queue.c \

SRCS = main.c $(SRCS_NAME)

SRCS_FULL = $(addprefix $(SRCS_PATH), $(SRCS))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS:.c=.o))

all:$(NAME)

$(NAME) : $(OBJ)
	@make -w -C $(LIBFT_DIRECTORY)
	@echo "\033[92m$(LIBFT_DIRECTORY)\033[0m compiled."
	@gcc $(FLAGS) $(OBJ) $(INC) -L $(LIBFT_DIRECTORY) -lft -o $(NAME)
	@echo "\033[35m$(NAME)\033[0m created."

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c $(HEADERS)
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[33m$<\033[0m compiled."

clean:
	@make -w -C $(LIBFT_DIRECTORY)/ clean
	@/bin/rm -rf $(OBJ_PATH)

fclean: clean
	@make -w -C $(LIBFT_DIRECTORY)/ fclean
	@/bin/rm -rf $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re