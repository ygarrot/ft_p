/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:50:03 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 19:20:50 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/* this file contain basic user shell command */
/* they are use in func tab */

int *calc_depths(char *str, int *new_depths)
{
	static int	depths = 0;
	int	i;
	char	*tmp;
	int	set;

	i = -1;
	set = 0;
	*new_depths = 0;
	if (!str)
		return (&depths);
	while (str[++i])
		if (!ft_strncmp(&str[i], "..", 2) && ++i && (set = 1))
			++*new_depths;
		else if (i > 0 && ft_strncmp(&str[i], "/.", 2)
				&& str[i] == '/'  && str[i + 1])
		{
			tmp = ft_strndup(str, i +1+ ft_strlento(&str[i+1], '/') );
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
	(void)str;
	return (redirect_command("/bin/ls",str, fd));
}

int		ft_pwd(int fd, char **str)
{
	(void)str;
	return (redirect_command("/bin/pwd",str, fd));
}

int		ft_cd(int fd, char **str)
{
	const char *arg[2] = {str[1], NULL};
	int *depths;
	int new_depths;

	if (!(depths = calc_depths(str[1], &new_depths)))
		return (ft_send("ERROR\n", fd));
	if (cd((char**)&arg, &g_env) >= 0)
		*depths -= new_depths;
	else
		return (ft_send("ERROR\n", fd));
	ft_send("OK\n", fd);
	return (1);
}
