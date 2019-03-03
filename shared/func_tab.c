/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:21:21 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 19:10:16 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int (*get_cmd(char *cmd, t_func_dic *ft))(int fd, char **string)
{
	int		i;

	i = -1;
	while (ft[++i].name)
		if (!ft_strcmp(cmd, ft[i].name))
			return (ft[i].function);
	return (NULL);
}


