/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:50:03 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/08 12:38:57 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** this file contain basic user shell command
** they are used in func tab
*/

int		ft_ls(int fd, char **str)
{
	return (redirect_command(LS_PATH, str, fd));
}

int		ft_pwd(int fd, char **str)
{
	return (redirect_command(PWD_PATH, str, fd));
}

int		ft_cd(int fd, char **str)
{
	int			depth;
	int			*last;
	const char	*arg[2] = {str[1], NULL};

	if (cd((char**)&arg, &g_env) < 0)
		return (ft_send(REQUEST_ERROR, fd));
	if (ft_strncmp(ft_getenv(g_env, "HOME"),
		ft_getenv(g_env, "PWD"), ft_strlen(ft_getenv(g_env, "HOME"))))
	{
		ft_send(NACCESS_PARENT, fd);
		arg[0] = ft_getenv(g_env, "HOME");
		cd((char**)&arg, &g_env);
	}
	else
		ft_send(REQUEST_OK, fd);
	last = calc_depths(&ft_getenv(g_env, "PWD")
	[ft_strlen(ft_getenv(g_env, "HOME"))], &depth, 1);
	*last -= depth;
	if (!ft_strlen(&ft_getenv(g_env, "PWD")
	[ft_strlen(ft_getenv(g_env, "HOME"))]))
		*last = 0;
	return (0);
}
