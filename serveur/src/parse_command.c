/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:03:53 by ygarrot           #+#    #+#             */
/*   Updated: 2019/08/17 13:27:50 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

static char	*must_quit(int filedes)
{
	char		*buffer;

	buffer = NULL;
	if (get_next_line(filedes, &buffer) <= 0)
		return (NULL);
	if (!ft_strcmp(buffer, "quit"))
	{
		ft_memdel((void**)&buffer);
		return (NULL);
	}
	ft_printf("Server: got message: `%s'\n", buffer);
	return (ft_strdup(buffer));
}

int			read_from_client(int filedes)
{
	char		*buffer;
	char		**to_del;
	t_func_dic	*fdic_server;

	fdic_server = (t_func_dic[CMD_NBR]){
	{"cd", ft_cd},
	{"ls", ft_ls},
	{"put", ft_get},
	{"get", ft_put},
	{"pwd", ft_pwd},
	{"mkdir", ft_mkdir},
	{"rmdir", ft_rmdir},
	{"unlink", ft_unlink}
	};
	if (!(buffer = must_quit(filedes)))
		return (-1);
	if (!(to_del = handle_command(filedes, buffer, fdic_server, 1)))
		ft_send(NO_CMD, filedes);
	ft_free_dblechar_tab(to_del);
	ft_memdel((void**)&buffer);
	return (0);
}
