/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:21:21 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/07 16:12:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int				get_cmd(char *cmd, t_func_dic *dic,
	int (**ft)(int, char**))
{
	int		i;

	i = -1;
	while (dic[++i].name)
		if (!ft_strcmp(cmd, dic[i].name))
		{
			*ft = dic[i].function;
			return (1);
		}
	return (0);
}
