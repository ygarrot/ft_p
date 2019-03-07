/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:50:23 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/07 11:24:09 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	interpret_command(int filedes, char *buffer)
{
	t_func_dic	*local_fun;
	t_func_dic	*fdic_server;

	local_fun = (t_func_dic[CMD_NBR]){
	{"lcd", ft_cd},
	{"lls", ft_ls},
	{"lpwd", ft_pwd}};
	fdic_server = (t_func_dic[CMD_NBR]){
			{"get", ft_get},
			{"put", ft_put}
	};
	if (-1 == ft_strisin_tab(buffer, CLIENT_TAB, 3))
	{
		ft_putendl_fd(buffer, filedes);
		if (ft_strncmp(buffer, "get", 3) && ft_strncmp(buffer, "put", 3))
			ft_receive(filedes, 1);
	}
	if (handle_command(filedes, buffer, (t_func_dic*)fdic_server, 0) < 0)
		return (1);
	else if (handle_command(1, buffer, (t_func_dic*)local_fun, 0) < 0)
		return (1);
	return (0);
}

int	read_loop(char *addr, int port)
{
	int		sock;
	char	*line;

	sock = create_client(addr, port);
	ft_printf("{boldblue}%s{reset} ☯ ", ft_getenv(g_env, "PWD"));
	while (get_next_line(0, &line) > 0)
	{
		if (!ft_strncmp(line, "quit", 4)
			|| interpret_command(sock, line))
			break ;
		ft_memdel((void**)&line);
		ft_printf("{boldblue}%s{reset} ☯ ", ft_getenv(g_env, "PWD"));
	}
	ft_memdel((void**)&line);
	ft_putendl("Good Bye");
	close(sock);
	return (0);
}
