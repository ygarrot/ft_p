/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 11:29:02 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
char **g_env;

int create_client(char *addr, int port)
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
	read_loop(av[1], ft_atoi(av[2]));
	return 1;
}
