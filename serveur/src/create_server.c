/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 12:21:09 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 14:35:54 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int	create_server(char *address, int port)
{
	int			sock;
	int			reuseaddr = 1;
	t_sockaddr *s_sock;

	sock = set_socket(ip_version(address) == 4);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
	s_sock = get_sock_addr(address, port, 1);
	/* ft_printf("%d %d %d\n",AF_INET6, AF_INET, s_sock->sa_family); */
	if (bind(sock, s_sock, ip_version(address) == 4 ? sizeof(t_sockaddr_in) : sizeof(t_sockaddr_in6)) == ERROR_CODE)
		ft_exit(BIND_ERROR, EXIT_FAILURE);
	ft_memdel((void**)&s_sock);
	listen(sock, 42);
	return (sock);
}

