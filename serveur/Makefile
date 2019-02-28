# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/02/27 14:38:41 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = serveur 

FLAGS = -Wall -Werror -Wextra
FLAGS += -fsanitize=address,undefined -g3
SRC_FOLDER = src/

INCLUDE =  includes/\
					 -I ../includes/

OBJ_DIR = mkdir obj

SRC_FP =\
				main.c

OBJ = $(addprefix $(SRC_FOLDER), $(SRC_FP:.c=.o))

LIBFT = ../libft/libft.a

all: $(NAME)

src/%.o: src/%.c
	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

$(NAME): $(OBJ)
	@make -C ../libft -j
	@gcc $(FLAGS) -o $(NAME) $(OBJ) -I $(INCLUDE) -L ../libft -l ft

clean:
	@rm -f $(OBJ)
	@make -C ../libft clean

fclean:
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -f $(NAME_NO_HOST)
	@make -C ../libft fclean

re: fclean all

.PHONY: $(NAME) all clean fclean re
