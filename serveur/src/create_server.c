/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 12:21:09 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 12:23:49 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int	create_server(char *address, int port)
{
	int			sock;
	int			reuseaddr;
	t_sockaddr *s_sock;

	sock = set_socket(ip_version(address) == 4);
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
	s_sock = get_sock_addr(address, port);
	if (bind(sock, s_sock, sizeof(t_sockaddr)) == ERROR_CODE)
		ft_exit(BIND_ERROR, EXIT_FAILURE);
	ft_memdel((void**)&s_sock);
	listen(sock, 42);
	return (sock);
}

