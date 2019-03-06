/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 12:21:09 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 12:54:28 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int	create_server(char *address, int port)
{
	int			sock;
	int			reuseaddr = 1;
	t_sockaddr_in6 sin2;
	t_sockaddr_in sin;
	t_sockaddr	*s_sock;

	sock = set_socket(ip_version(address) == 4);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
	&reuseaddr, sizeof(reuseaddr));
	s_sock = ip_version(address) == 4 ?
	(t_sockaddr*)get_ipv4_addr(NULL, port, &sin)
	: (t_sockaddr*)get_ipv6_addr(NULL, port, &sin2);
	if (bind(sock , s_sock, ip_version(address) == 4 ?
		sizeof(t_sockaddr_in) : sizeof(t_sockaddr_in6)) == ERROR_CODE)
		ft_exit(BIND_ERROR, EXIT_FAILURE);
	listen(sock, 42);
	return (sock);
}

