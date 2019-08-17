# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/08/15 13:06:14 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re client serveur

NAME = ft_p 

all: $(NAME)

$(NAME): client serveur

client:
	@make -C client

serveur:
	@make -C serveur

clean:
	@make -C serveur clean
	@make -C client clean

fclean:
	make -C serveur fclean
	make -C client fclean

re: fclean all
