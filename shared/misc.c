/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:50:03 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 15:27:58 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** this file contain basic user shell command
** they are used in func tab
*/

int		*calc_depths(char *str, int *new_depths)
{
	static int	depths = 0;
	int			i;
	char		*tmp;
	int			set;

	i = -1;
	set = 0;
	*new_depths = 0;
	if (!str)
		return (&depths);
	while (str[++i])
		if (!ft_strncmp(&str[i], "..", 2) && ++i && (set = 1))
			++*new_depths;
		else if (i > 0 && ft_strncmp(&str[i], "/.", 2)
				&& str[i] == '/' && str[i + 1])
		{
			tmp = ft_strndup(str, i + 1 + ft_strlento(&str[i + 1], '/'));
			if (is_directory_str(tmp) == 1 && (set = 1))
				--*new_depths;
			ft_memdel((void**)&tmp);
		}
	*new_depths = (set ? *new_depths : -1);
	if (str[0] == '/' || (depths - *new_depths) < 0)
		return (NULL);
	return (&depths);
}

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
	char	*arg[2] = {str[1], NULL};
	if (cd((char**)&arg, &g_env) < 0)
		return (ft_send(REQUEST_ERROR, fd));
	if (ft_strncmp(ft_getenv(g_env, "HOME"), ft_getenv(g_env, "PWD"), ft_strlen(ft_getenv(g_env, "HOME"))))
	{
		ft_send(REQUEST_ERROR, fd);
		arg[0] = ft_getenv(g_env, "HOME");
		cd((char**)&arg,&g_env);
	}
	else
		ft_send(REQUEST_OK, fd);
	return (1);
}
