# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/02/28 15:25:10 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re

NAME = serveur

FLAGS = -Wall -Werror -Wextra
FLAGS += -fsanitize=address,undefined -g3
SRC_FOLDER = src/

INCLUDE =  includes/\
		   -I ../includes/

OBJ_DIR = mkdir obj

SRC_FP =\
		redirect_command.c\
		ft_cd.c\
		ft_env.c\
		ft_setenv.c\
		select.c\
		make_socket.c\
		main.c


OBJ = $(addprefix $(SRC_FOLDER), $(SRC_FP:.c=.o))

LIBFT = ../libft/libft.a

all: $(NAME)

src/%.o: src/%.c
	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

$(NAME): $(OBJ)
	@make -C ../libft
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(INCLUDE) -L ../libft -l ft

clean:
	@rm -f $(OBJ)
	@make -C ../libft clean

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@make -C ../libft fclean

re: fclean all

