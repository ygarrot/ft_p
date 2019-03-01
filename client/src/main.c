/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/01 17:01:42 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int create_serveur(char *addr, int port)
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
	sin.sin_addr.s_addr = inet_addr(addr);
	if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) == -1)
	{
		printf("Bind error\n");
		exit(2);
	}
	return (sock);
}

int main(int ac, char *av[], char **env)
{
	(void)ac;(void)av;(void)env;
	if (ac < 3)
	{
		ft_printf("Please give me a port and an address\n");
		return 1;
	}
	int sock = create_serveur(av[1], ft_atoi(av[2]));
	write(sock, "test\nretest\n", 10);
	/* init_serveur(ft_atoi(av[1])); */
	while(1);
	return 0;
}
