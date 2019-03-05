/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 14:36:21 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"
char **g_env;

int create_client(char *address, int port)
{
	int			sock;
	t_sockaddr *s_sock;

	sock = set_socket(ip_version(address) == 4);
	s_sock = get_sock_addr(address, port, 0);
	if (connect(sock, s_sock, sizeof(t_sockaddr)) == ERROR_CODE)
		ft_exit(BIND_ERROR, EXIT_FAILURE);
	ft_memdel((void**)&s_sock);
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
	g_env = env;
	read_loop(av[1], ft_atoi(av[2]));
	return 1;
}
