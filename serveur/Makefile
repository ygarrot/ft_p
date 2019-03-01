# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/03/01 14:39:39 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re

NAME = serveur

FLAGS = -Wall -Werror -Wextra
FLAGS += -fsanitize=address,undefined -g3
SRC_DIR = src

INCLUDE =  includes/\
		   -I ../includes/

OBJ_DIR = obj

SRC =\
		../../get.c\
		../../put.c\
		redirect_command.c\
		ft_cd.c\
		ft_env.c\
		ft_setenv.c\
		select.c\
		make_socket.c\
		main.c


SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))

OBJ_FILES = $(sort $(dir $(OBJS)))

LIBFT = ../libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

$(NAME): obj_dir $(OBJS) 
	@make -C ../libft
	@gcc $(FLAGS) -o $(NAME) $(OBJS) -I $(INCLUDE) -L ../libft -l ft

obj_dir:
	@mkdir obj || true

clean:
	@rm -rf $(OBJ_DIR)
	@make -C ../libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ../libft fclean

re: fclean all

