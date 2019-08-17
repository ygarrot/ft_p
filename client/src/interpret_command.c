/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:50:23 by ygarrot           #+#    #+#             */
/*   Updated: 2019/08/17 13:15:33 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

void	print_state(char *buffer, int filedes)
{
	char	*ret;
	int		lenn;

	if (!buffer)
		return ;
	lenn = ft_strlento(buffer, ' ');
	if (!ft_strncmp(buffer, "get", lenn)
		|| !ft_strncmp(buffer, "put", lenn))
		return ;
	ret = ft_receive_str(filedes);
	ft_printf("%s\n", ret);
	if (!ret)
	{
		ft_printf("{boldgreen}[ SUCCESS ]{reset} %s\n", buffer);
		return ;
	}
	ft_printf(ret && ft_strncmp("ERROR", ret, ft_strlen("ERROR"))
	? "{boldgreen}[ SUCCESS ]{reset} %s\n%s"
	: "{boldred}[ ERROR ]{reset} %s\n%s", buffer, ret);
	ft_memdel((void**)&ret);
}

int		interpret_command(int filedes, char *buffer)
{
	t_func_dic	*local_fun;
	t_func_dic	*fdic_server;
	int			is_serv;
	char		**tmp;

	is_serv = 0;
	local_fun = (t_func_dic[CMD_NBR]){
		{"lcd", ft_cd},
		{"lls", ft_ls},
		{"lpwd", ft_pwd}};
	fdic_server = (t_func_dic[CMD_NBR]){
		{"get", ft_get},
		{"put", ft_put}
	};
	if (-1 == ft_strisin_tab(buffer, CLIENT_TAB, 3) && (is_serv = 1))
	{
		ft_putendl_fd(buffer, filedes);
		print_state(buffer, filedes);
	}
	if (!(tmp = handle_command(filedes, buffer, (t_func_dic*)fdic_server, 0)))
		tmp = handle_command(1, buffer, local_fun, 0);
	if (!is_serv && !tmp)
		ft_printf("{boldred}[ ERROR ]{reset} %s\n%s", buffer, NO_CMD);
	ft_free_dblechar_tab(tmp);
	return (0);
}

int		read_loop(char *addr, int port)
{
	int		sock;
	char	*line;

	sock = create_client(addr, port);
	ft_printf("{boldblue}%s{reset} ☯ ", ft_getenv(g_env, "PWD"));
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strlen(line) && (!ft_strncmp(line, "quit", 4)
					|| interpret_command(sock, line)))
			break ;
		ft_memdel((void**)&line);
		ft_printf("{boldblue}%s{reset} ☯ ", ft_getenv(g_env, "PWD"));
	}
	ft_memdel((void**)&line);
	ft_putendl("Good Bye");
	close(sock);
	return (0);
}
