/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:36:31 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 14:58:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int	handle_command(int fd, char *str)
{
	int (*ft)(int, char*);
	char	**argv;
	const t_func_dic *fdic_server = (t_func_dic[CMD_NBR]){
	{"cd", ft_cd},
	{"ls", ft_ls},
	{"put", ft_put},
	{"get", ft_get},
	{"pwd", ft_pwd},
	/* {"quit", ft_quit} */
};
	str[ft_strlento(str, '\n')] = '\0';
	if (!(argv = ft_strsplit(str, ' ')))
		return (0);
	if (!(ft = get_cmd(argv[0], (t_func_dic*)fdic_server)))
		return (1);
	return (ft(fd, argv[1]));
}
