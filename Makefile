# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/02/27 14:33:53 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_p 

all: $(NAME)

$(NAME): $(OBJ)
	@make -C serveur
	# @make -C otool 

clean:
	@make -C serveur
	# @make -C otool 

fclean:
	make -C serveur fclean
	# make -C otool fclean

re: fclean all

.PHONY: $(NAME) all clean fclean re
