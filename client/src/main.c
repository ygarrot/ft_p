/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 18:22:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

char **g_env;

int	create_client(char *address, int port)
{
	int				sock;
	t_sockaddr_in6	sin2;
	t_sockaddr_in	sin;
	t_sockaddr		*s_sock;

	sock = set_socket(ip_version(address) == 4);
	s_sock = ip_version(address) == 4 ?
	(t_sockaddr*)get_ipv4_addr(address, port, &sin)
	: (t_sockaddr*)get_ipv6_addr(address, port, &sin2);
	if (connect(sock, s_sock, ip_version(address) == 4 ?
		sizeof(t_sockaddr_in)
	: sizeof(t_sockaddr_in6)) == ERROR_CODE)
		ft_exit(BIND_ERROR, EXIT_FAILURE);
	return (sock);
}

int	main(int ac, char *av[], char **env)
{
	if (ac < 3)
	{
		ft_printf("Please give me a port and an address\n");
		return (1);
	}
	if (!ft_getenv(g_env, "PWD") || !ft_getenv(g_env, "HOME"))
		return (ft_printf("%s\n", NO_PWD));
	g_env = ft_strtabdup(env);
	read_loop(av[1], ft_atoi(av[2]));
	return (1);
}
