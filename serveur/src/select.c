/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:27:48 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 12:17:18 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int read_from_client (int filedes)
{
	char buffer[MAXMSG];
	int nbytes;

	nbytes = read (filedes, buffer, MAXMSG);
	if (nbytes < 0)
	{
		/* Read error. */
		ft_printf ("read");
		exit (EXIT_FAILURE);
	}
	else if (nbytes == 0)
		/* End-of-file. */
		return -1;
	else
	{
		/* Data read. */
		ft_printf ("Server: got message: `%s'\n", buffer);
		return 0;
	}
	return 0;
}

int	handle_active_socket(fd_set active_fd_set, int i)
{
	if (read_from_client(i) < 0)
	{
		close (i);
		FD_CLR (i, &active_fd_set);
	}
	return 0;
}

int handle_new_socket(fd_set active_fd_set, int sock)
{
	int				new;
  	t_sockaddr_in	clientname;
	unsigned int	size;


	size = sizeof(clientname);
	if ((new = accept(sock, (t_sockaddr*)&clientname, &size)) < 0)
	{
		/* TODO: handle error */
	}
	ft_printf ("Server: connect from host %s, port %hd.\n",
			inet_ntoa (clientname.sin_addr),
			ntohs (clientname.sin_port));
	FD_SET (new, &active_fd_set);
	return 0;
}

int		eval_loop(fd_set active_fd_set, fd_set read_fd_set, int sock)
{
	int		i;

	i = -1;
	while (++i < FD_SETSIZE)
	{
		if (FD_ISSET (i, &read_fd_set))
			handle_new_socket(active_fd_set, sock);
		else
			handle_active_socket(active_fd_set, i);
	}
	return 0;
}

int		init_serveur()
{
	fd_set active_fd_set, read_fd_set;
	int sock;

	/* Create the socket and set it up to accept connections. */
	sock = make_socket (PORT);
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
		eval_loop(active_fd_set, read_fd_set, sock);
	}
	return 0;
}
