/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:54:37 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 12:24:21 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	set_socket(int is_ipv4)
{
	int			sock;
	t_protoent	*proto;

	if (!(proto = getprotobyname("tcp")))
		return (0);
	if ((sock = socket(is_ipv4 ? AF_INET : AF_INET6, SOCK_STREAM, proto->p_proto)) < -1)
		ft_exit(SOCKET_ERROR, EXIT_FAILURE);
	return (sock);
}

t_sockaddr_in	*get_ipv4_addr(char *address, int port)
{
	t_sockaddr_in	*sin;

	(void)address;
	if (!(sin = (t_sockaddr_in*)ft_memalloc(sizeof(t_sockaddr_in))))
		return (NULL);
	sin->sin_family = AF_INET;
	sin->sin_port = htons(port);
	sin->sin_addr.s_addr = inet_addr(address);
	return (sin);
}

t_sockaddr_in6	*get_ipv6_addr(char *address, int port)
{
	t_sockaddr_in6	*sin;

	(void)address;
	sin = (t_sockaddr_in6*)ft_memalloc(sizeof(t_sockaddr_in6));
		return (NULL);
	sin->sin6_family = AF_INET6;
	sin->sin6_port = htons(port);
	inet_pton(AF_INET6, address, &sin->sin6_addr);
	return (sin);
}

t_sockaddr	*get_sock_addr(char *addr,  int port)
{
	if (ip_version(addr) == 4)
		return ((t_sockaddr*)get_ipv4_addr(addr, port));
	else if (ip_version(addr) == 6)
		return ((t_sockaddr*)get_ipv6_addr(addr, port));
	return (NULL);
}

