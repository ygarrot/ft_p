/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:27:48 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/01 17:23:52 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int read_from_client (int filedes)
{
	char buffer[MAXMSG];
	int nbytes;

	nbytes = read (filedes, buffer, MAXMSG);
	buffer[nbytes] = '\0';
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
		/* char *arg[] = {"..", NULL}; */
		/* ft_cd(arg, &g_env); */
	/* write(filedes, "200", 3); */
		/* put(filedes, "tmp"); */
		if (ft_strstr(buffer, "EPSV"))
	   		dprintf(filedes, "%d\r\n", 150);
		if (ft_strstr(buffer, "EPSV"))
	   		dprintf(filedes, "%d\r\n", 227);
		else
	   		dprintf(filedes, "%d\r\n", 229);
		return 0;
	}
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
	/* int i = 0; */
	/* while (++i < 600) */
		/* { */
			/* printf("%d\n", i); */
	   /* dprintf(new, "%d\r\n", i); */
	   		/* usleep(60000); */
		/* } */
	/* write(new, "500 OK \r\n\n", 5); */
	/* write(new, "500 OK \r\n", 5); */
	/* write(new, "500 OK \r\n", 5); */
	write(new, "0\r\n", 3);
	/* write(sock, "500 OK\r\n", 5); */
	/* send(new, "200 OK\r\n", 5, 0); */
	/* ft_printf("new %d\n", new); */
	/* send(sock, "200 OK\r\n", 5, 0); */
	/* write(sock, "200\r\n", 5); */
	return 0;
}

int		eval_loop(fd_set *active_fd_set, fd_set *read_fd_set, int sock)
{
	int		i;

	i = -1;
	while (++i < FD_SETSIZE)
	{
		if (FD_ISSET (i, read_fd_set))
		{
			ft_printf("received message from: %d\n", i);
			if (i == sock)
				handle_new_socket(active_fd_set, sock);
			else
				handle_active_socket(active_fd_set, i);
		}
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
