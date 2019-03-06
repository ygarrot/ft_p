/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_creation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 11:54:37 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 17:52:05 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				set_socket(int is_ipv4)
{
	int			sock;
	t_protoent	*proto;

	if (!(proto = getprotobyname("tcp")))
		return (0);
	if ((sock = socket(is_ipv4 ? AF_INET
		: AF_INET6, SOCK_STREAM, proto->p_proto)) < -1)
		ft_exit(SOCKET_ERROR, EXIT_FAILURE);
	return (sock);
}

t_sockaddr_in	*get_ipv4_addr(char *address, int port, t_sockaddr_in *sin)
{
	sin->sin_family = AF_INET;
	sin->sin_port = htons(port);
	if (!address)
		sin->sin_addr.s_addr = htonl(INADDR_ANY);
	else
		sin->sin_addr.s_addr = inet_addr(address);
	return (sin);
}

t_sockaddr_in6	*get_ipv6_addr(char *address, int port, t_sockaddr_in6 *sin)
{
	sin->sin6_family = AF_INET6;
	sin->sin6_port = htons(port);
	if (!address)
		sin->sin6_addr = in6addr_any;
	else
		inet_pton(AF_INET6, address, &sin->sin6_addr);
	return (sin);
}
