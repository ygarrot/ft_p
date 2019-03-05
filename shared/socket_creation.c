/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:54:37 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 14:28:40 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	set_socket(int is_ipv4)
{
	int			sock;
	t_protoent	*proto;

	if (!(proto = getprotobyname("tcp")))
		return (0);
	if ((sock = socket(is_ipv4 ? AF_INET : AF_INET6, SOCK_STREAM, 0)) < -1)
		ft_exit(SOCKET_ERROR, EXIT_FAILURE);
	return (sock);
}

t_sockaddr *get_ipv4_addr(char *address, int port)
{
	t_sockaddr_in *sin;

	(void)address;
	if (!(sin = (t_sockaddr_in*)ft_memalloc(sizeof(t_sockaddr_in))))
		return 0;
	sin->sin_family = AF_INET;
	sin->sin_port = htons(port);
	if (!address)
	{
		sin->sin_addr.s_addr = htonl (INADDR_ANY);
	}
	else
		sin->sin_addr.s_addr = inet_addr(address);
	return (t_sockaddr*)sin;
}

t_sockaddr *get_ipv6_addr(char *address, int port)
{
	t_sockaddr_in6 *sin;

	(void)address;
	if (!(sin = (t_sockaddr_in6*)ft_memalloc(sizeof(t_sockaddr_in6))))
		return 0;
	sin->sin6_family = AF_INET6;
	sin->sin6_port = htons(port);
	if (!address)
	{
		ft_printf("test\n");
		/* inet_pton(AF_INET6, "::1", &sin->sin6_addr); */
		sin->sin6_addr = in6addr_any;
		/* sin->sin6_addr = in6addr_loopback; */
	}
	else
		inet_pton(AF_INET6, address, &sin->sin6_addr);
	return (t_sockaddr*)sin;
}

t_sockaddr	*get_sock_addr(char *addr,  int port, int is_serv)
{
	if (ip_version(addr) == 4)
		return (get_ipv4_addr(is_serv ? NULL : addr, port));
	else if (ip_version(addr) == 6)
		return (get_ipv6_addr(is_serv ? NULL : addr, port));
	return (NULL);
}

