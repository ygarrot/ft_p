# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/03/07 15:28:44 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re client serveur

NAME = ft_p 

all: $(NAME)


client:
	@make -C client

serveur:
	@make -C serveur

$(NAME): client serveur

clean:
	@make -C serveur
	@make -C client 

fclean:
	make -C serveur fclean
	make -C client fclean

re: fclean all
