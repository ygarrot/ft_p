# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/03/01 14:23:55 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re

NAME = ft_p 

all: $(NAME)

$(NAME): $(OBJ)
	@make -C serveur
	@make -C client 

clean:
	@make -C serveur
	@make -C client 

fclean:
	make -C serveur fclean
	make -C client fclean

re: fclean all
