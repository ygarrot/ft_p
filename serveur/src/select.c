/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 11:27:48 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 11:44:55 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int read_from_client (int filedes)
{
	char buffer[MAXMSG];
	int nbytes;

	nbytes = read (filedes, buffer, MAXMSG);
	if (nbytes < 0)
	{
		/* Read error. */
		perror ("read");
		exit (EXIT_FAILURE);
	}
	else if (nbytes == 0)
		/* End-of-file. */
		return -1;
	else
	{
		/* Data read. */
		fprintf (stderr, "Server: got message: `%s'\n", buffer);
		return 0;
	}
}

int	handle_active_socket()
{
	if (read_from_client(i) < 0)
	{
		close (i);
		FD_CLR (i, &active_fd_set);
	}
}

int handle_new_socket()
{
	int	new;
	size_t	size;

	size = sizeof(clientname);
	if ((new = accept(sock, (t_sockaddr*)&clientname, &size)) < 0)
	{
		/* TODO: handle error */
	}
	fprintf (stderr,
			"Server: connect from host %s, port %hd.\n",
			inet_ntoa (clientname.sin_addr),
			ntohs (clientname.sin_port));
	FD_SET (new, &active_fd_set);
}

int		eval_loop()
{
	int		i;

	i = -1;
	while (++i < FD_SETSIZE)
	{
		if (FD_ISSET (i, &read_fd_set))
			handle_new_socket();
		else
			handle_active_socket();
	}
}

int		init_serveur()
{
	fd_set active_fd_set, read_fd_set;
	int sock;

/* Create the socket and set it up to accept connections. */
	sock = make_socket (PORT);
	if (listen (sock, 1) < 0)
	{
		perror ("listen");
		exit (EXIT_FAILURE);
	}
/* Initialize the set of active sockets. */
	FD_ZERO (&active_fd_set);
	FD_SET (sock, &active_fd_set);
	while (true)
	{
	/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;
		eval_loop();
		if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			perror ("select");
			exit (EXIT_FAILURE);
		}
	}
}
