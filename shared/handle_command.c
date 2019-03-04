/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:36:31 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/04 12:07:23 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** alternate to func dic
*/

int	handle_command(int fd, char *str, t_func_dic *fdic)
{
	int		(*ft)(int, char**);
	char	**argv;
	int		ret;

	str[ft_strlento(str, '\n')] = '\0';
	if (!(argv = ft_strsplit(str, ' ')))
		return (0);
	if (!(ft = get_cmd(argv[0], (t_func_dic*)fdic)))
		return (1);
	ret = ft(fd, argv);
	ft_free_dblechar_tab(argv);
	return (ret);
}
