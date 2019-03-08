# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/04/11 13:13:35 by ygarrot           #+#    #+#              #
#    Updated: 2019/03/08 19:03:01 by ygarrot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: $(NAME) all clean fclean re

NAME = serveur

FLAGS = -Wall -Werror -Wextra
FLAGS += -g3
# FLAGS += -fsanitize=address,undefined
SRC_DIR = src

INCLUDE =  includes/\
		   -I ../includes/

SHARED_DIR = ../shared
OBJ_DIR = obj

SRC =\
	 main.c\
	 create_server.c\
	 parse_command.c\
	 select.c

SHARED_SRC = \
			 misc.c\
			 ft_exit.c\
			 ip_version.c\
			 socket_creation.c\
			 handle_command.c\
			 socket.c\
			 bonus.c\
			 ft_cd.c\
			 ft_env.c\
			 ft_setenv.c\
			 func_tab.c\
			 get.c\
			 put.c\
			 redirect_command.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

SHARED_SRCS = $(addprefix $(SHARED_DIR)/, $(SHARED_SRC))

OBJS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(basename $(SRC))))
SHARED_OBJS = $(addprefix ../$(OBJ_DIR)/, $(addsuffix .o, $(basename $(SHARED_SRC))))

OBJ_FILES = $(sort $(dir $(OBJS) $(dir $SHARED_OBJS)))

LIBFT = ../libft/libft.a

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c includes/$(NAME).h
	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

../$(OBJ_DIR)/%.o: $(SHARED_DIR)/%.c
	@gcc $(FLAGS) -o $@ -c $<  -I $(INCLUDE)

$(NAME): obj_dir $(OBJS) $(SHARED_OBJS) 
	@make -C ../libft
	@gcc $(FLAGS) -o $(NAME) $(OBJS) $(SHARED_OBJS) -I $(INCLUDE) -L ../libft -l ft
	@echo $(NAME) is compiled

obj_dir:
	@mkdir -p $(OBJ_DIR) || true
	@mkdir -p ../$(OBJ_DIR) || true

clean:
	@rm -rf $(OBJ_DIR)
	@rm -rf ../$(OBJ_DIR)
	@make -C ../libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ../libft fclean

re: fclean all

