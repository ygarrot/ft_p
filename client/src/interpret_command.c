/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:50:23 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 19:47:59 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_serveur_output(int fd)
{
	char *line;

	while (get_next_line(fd, &line) > 0)
	{
		if (!ft_strcmp("200", line))
			return ;
		ft_putendl(line);
		ft_memdel((void**)&line);
	}
}

int	interpret_command(int filedes, char *buffer)
{
	/* char *buffer; */
	const t_func_dic *local_fun = (t_func_dic[CMD_NBR]){
	{"lcd", ft_cd},
	{"lls", ft_ls},
	{"lpwd", ft_pwd},
	};
	const t_func_dic *fdic_server = (t_func_dic[CMD_NBR]){
			{"get", ft_get},
			{"put", ft_put},
			/* {"quit", ft_quit} */
	};

	ft_send(buffer, filedes);
	/* ft_putendl_fd(buffer, filedes); */
	if (ft_strncmp("get", buffer, 3) && ft_strncmp("put", buffer, 3))
		ft_receive(filedes, 1);
	(void)fdic_server;(void)local_fun;
	if (handle_command(filedes, buffer, (t_func_dic*)fdic_server) < 0)
		return (1);
	else if (handle_command(1, buffer, (t_func_dic*)local_fun) < 0)
		return (1);
	ft_memdel((void**)&buffer);
	return 0;
}

int	read_loop(char *addr, int port)
{
	int sock;
	char *line;

	sock = create_client(addr, port);
	/* if (get_next_line(sock, &line) <= 0 || ft_strcmp("OK", line)) */
	/* 	return 1; */
	/* ft_memdel((void**)&line); */
	ft_printf(">");
	while (get_next_line(0, &line) > 0)
	{
		/* ft_putendl(""); */
		ft_printf("received %s\n", line);
		if (interpret_command(sock, line))
			break ;
		ft_printf(">");
	}
	ft_putendl("Good Bye");
	close(sock);
	return 0;
}
