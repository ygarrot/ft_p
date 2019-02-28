/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/27 15:42:05 by ygarrot          ###   ########.fr       */
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
	int			port;
	int			sock;
	int			cs;
	unsigned int	cslen;
	struct sockaddr_in	csin;
	char		buf[1024];
	int			r;
	(void)av;
	(void)ac;

	port = atoi(av[1]);
	sock = create_seveur(port);
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);
	while((r = read(cs, buf, 1023)) > 0)
	{
		buf[r] = '\0';
		ft_printf("received %d bytes: [%s]\n", r, buf);
	}
	close(cs);
	close(sock);
	return 0;
}
