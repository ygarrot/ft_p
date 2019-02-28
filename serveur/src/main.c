/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 12:23:49 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int create_seveur(int port)
{
	int		sock;
	struct	protoent	*proto;
	struct sockaddr_in sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		return (-1);
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		printf("Bind error\n");
		exit(2);
	}
	listen(sock, 42);
	return (sock);
}

int main(int ac, char *av[])
{
	(void)ac;(void)av;
	init_serveur();
	return 0;
}
