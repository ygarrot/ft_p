/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:36:31 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 17:46:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** alternate to func dic
*/

int	handle_command(int fd, char *str, t_func_dic *fdic, int is_server)
{
	int		(*ft)(int, char**);
	char	**argv;
	int		ret;

	str[ft_strlento(str, '\n')] = '\0';
	if (!(argv = ft_strsplit(str, ' ')))
		return (0);
	if (!(ft = get_cmd(argv[0], (t_func_dic*)fdic)))
		return (1);
	if (is_server && argv[1])
		argv[2] = NULL;
	if (is_server && argv[1] && ft_strcmp(argv[0], "put")
		&& ft_strcmp(argv[0], "cd") && ft_strstr(argv[1], ".."))
	{
		ft_send(REQUEST_ERROR, fd);
		return (0);
	}
	else
		ret = ft(fd, argv);
	ft_free_dblechar_tab(argv);
	return (ret);
}
