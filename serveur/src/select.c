/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:27:48 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 14:56:52 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

#define COMMAND_SIZE 12

int read_from_client (int filedes)
{
	char buffer[COMMAND_SIZE];
	int nbytes;

	if ((nbytes = read (filedes, buffer, MAXMSG)) < 0)
	{
		ft_printf ("read");
		exit (EXIT_FAILURE);
	}
	else if (nbytes == 0)
		return -1;
	buffer[nbytes] = '\0';
	handle_command(filedes, buffer);
	ft_printf ("Server: got message: `%s'\n", buffer);
	return 0;
}

int	handle_active_socket(fd_set *active_fd_set, int sock)
{
	if (read_from_client(sock) < 0)
	{
		close (sock);
		FD_CLR (sock, active_fd_set);
	}
	return 0;
}

int handle_new_socket(fd_set *active_fd_set, int sock)
{
	int				new;
	t_sockaddr_in	clientname;
	unsigned int	size;

	size = sizeof(clientname);
	if ((new = accept(sock, (t_sockaddr*)&clientname, &size)) < 0)
	{
		ft_printf("accept failed\n");
		exit(EXIT_FAILURE);
		/* TODO: handle error */
	}
	ft_printf ("Server: connect from host %s, port %hd.\n",
			inet_ntoa (clientname.sin_addr),
			ntohs (clientname.sin_port));
	FD_SET (new, active_fd_set);
	return 0;
}

int		eval_loop(fd_set *active_fd_set, fd_set *read_fd_set, int sock)
{
	int		i;

	i = -1;
	while (++i < FD_SETSIZE)
	{
		if (!FD_ISSET (i, read_fd_set))
			continue;
		/* ft_printf("received message from: %d\n", i); */
		if (i == sock)
			handle_new_socket(active_fd_set, sock);
		else
			handle_active_socket(active_fd_set, i);
	}
	return 0;
}

int		init_serveur(int port)
{
	fd_set active_fd_set, read_fd_set;
	int sock;

	/* Create the socket and set it up to accept connections. */
	sock = make_socket (port);
	if (listen (sock, 1) < 0)
	{
		ft_printf ("listen");
		exit (EXIT_FAILURE);
	}
	/* Initialize the set of active sockets. */
	FD_ZERO (&active_fd_set);
	FD_SET (sock, &active_fd_set);
	while (true)
	{
		/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			ft_printf ("select");
			exit (EXIT_FAILURE);
		}
		eval_loop(&active_fd_set, &read_fd_set, sock);
	}
	return 0;
}
