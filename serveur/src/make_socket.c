/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_socket.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:26:42 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/04 14:05:01 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

/* int		make_socket (uint16_t port) */
/* { */
/* 	int sock; */
/* 	struct sockaddr_in name; */

/* 	/1* Create the socket. *1/ */
/* 	sock = socket (PF_INET, SOCK_STREAM, 0); */
/* 	if (sock < 0) */
/* 	{ */
/* 		perror ("socket"); */
/* 		exit (EXIT_FAILURE); */
/* 	} */

/* 	/1* Give the socket a name. *1/ */
/* 	name.sin_family = AF_INET; */
/* 	name.sin_port = htons (port); */
/* 	name.sin_addr.s_addr = htonl (INADDR_ANY); */
/* 	if (bind (sock, (struct sockaddr *) &name, sizeof (name)) < 0) */
/* 	{ */
/* 		perror ("bind"); */
/* 		exit (EXIT_FAILURE); */
/* 	} */

/* 	return sock; */
/* } */

int make_socket(uint16_t port)
{
	int		sock;
	struct	protoent	*proto;
	int reuseaddr = 1;
	struct sockaddr_in6 sin;

	proto = getprotobyname("tcp");
	
	if (proto == 0)
		return (-1);
	/* sock = socket(PF_INET, SOCK_STREAM, proto->p_proto); */
	if ((sock = socket(AF_INET6, SOCK_STREAM, 0) < -1))//, proto->p_proto);
		exit(2);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
	sin.sin6_family = AF_INET6;
	sin.sin6_port = htons((int)port);
	/* sin.sin6_addr.s_addr = htonl(INADDR_ANY); */
	/* sin.sin6_addr = htonl(INADDR_ANY); */
	sin.sin6_addr = in6addr_any;
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		perror("bind");
		exit(2);
	}
	listen(sock, 42);
	return (sock);
}

