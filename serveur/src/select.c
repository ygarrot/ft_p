/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:27:48 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 18:02:23 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		read_from_client(int filedes)
{
	char		*buffer;
	t_func_dic	*fdic_server;

	fdic_server = (t_func_dic[CMD_NBR]){
	{"cd", ft_cd},
	{"ls", ft_ls},
	{"put", ft_get},
	{"get", ft_put},
	{"pwd", ft_pwd},
	{"mkdir", ft_mkdir},
	{"rmdir", ft_rmdir},
	{"unlink", ft_unlink}
	};
	if (get_next_line_b(filedes, &buffer, 1) <= 0)
		return (-1);
	if (!ft_strcmp(buffer, "quit"))
		return (-1);
	ft_printf("Server: got message: `%s'\n", buffer);
	if (1
		== handle_command(filedes, buffer, (t_func_dic*)fdic_server, 1))
		ft_send(REQUEST_ERROR, filedes);
	ft_memdel((void**)&buffer);
	return (0);
}

int		handle_active_socket(fd_set *active_fd_set, int sock)
{
	if (read_from_client(sock) < 0)
	{
		close(sock);
		FD_CLR(sock, active_fd_set);
	}
	return (0);
}

int		handle_new_socket(fd_set *active_fd_set, int sock)
{
	int				new;
	t_sockaddr_in	clientname;
	unsigned int	size;

	size = sizeof(clientname);
	if ((new = accept(sock, (t_sockaddr*)&clientname, &size)) < 0)
		ft_exit(ACCEPT_ERROR, EXIT_FAILURE);
	ft_printf("Server: connect from host %s, port %hd.\n",
			inet_ntoa(clientname.sin_addr),
			ntohs(clientname.sin_port));
	FD_SET(new, active_fd_set);
	return (0);
}

int		eval_loop(fd_set *active_fd_set, fd_set *read_fd_set, int sock)
{
	int		i;

	i = -1;
	while (++i < FD_SETSIZE)
	{
		if (!FD_ISSET(i, read_fd_set))
			continue;
		if (i == sock)
			handle_new_socket(active_fd_set, sock);
		else
			handle_active_socket(active_fd_set, i);
	}
	return (0);
}

int		init_serveur(char *addr, int port)
{
	fd_set	active_fd_set;
	fd_set	read_fd_set;
	int		sock;

	sock = create_server(addr, port);
	if (listen(sock, QUEUE_LEN) < 0)
		ft_exit(LISTEN_ERROR, EXIT_FAILURE);
	FD_ZERO(&active_fd_set);
	FD_SET(sock, &active_fd_set);
	while (true)
	{
		read_fd_set = active_fd_set;
		if (select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL)
			== ERROR_CODE)
			ft_exit(SELECT_ERROR, EXIT_FAILURE);
		eval_loop(&active_fd_set, &read_fd_set, sock);
	}
	return (0);
}
