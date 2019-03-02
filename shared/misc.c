/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:50:03 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 14:53:52 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/* this file contain basic user shell command */
/* they are use in func tab */

int		ft_ls(int fd, char *str)
{
	(void)str;
	ft_printf("ls\n");
	return (redirect_command("/bin/ls",NULL, fd));
}

int		ft_pwd(int fd, char *str)
{
	(void)str;
	return (redirect_command("/bin/pwd",NULL, fd));
}

int		ft_cd(int fd, char *str)
{
	(void)fd;
	const char *arg[2] = {str, NULL};
	cd((char**)&arg, &g_env);
	return (1);
}
