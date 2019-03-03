/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:50:03 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 13:50:23 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/* this file contain basic user shell command */
/* they are use in func tab */

int *calc_depths(char *str, int *new_depths)
{
	static int depths = 0;
	int	i;
	int set;

	i = -1;
	set = 0;
	*new_depths = 0;
	while (str[++i])
		if (!ft_strncmp(&str[i], "..", 2) && ++i && (set = 1))
			++*new_depths;
		else if (i > 0 && ft_strncmp(&str[i], "/.", 2)
				&& str[i] == '/'  && str[i + 1] && (set = 1))
			--*new_depths;
	*new_depths = (set ? *new_depths : -1);
	if (str[0] == '/' || (depths - *new_depths) < 0)
		return (NULL);
	return (&depths);
}

int		ft_ls(int fd, char *str)
{
	(void)str;
	ft_printf("%d\n", fd);
	return (redirect_command("/bin/ls",NULL, fd));
}

int		ft_pwd(int fd, char *str)
{
	(void)str;
	return (redirect_command("/bin/pwd",NULL, fd));
}

int		ft_cd(int fd, char *str)
{
	const char *arg[2] = {str, NULL};
	int *depths;
	int new_depths;

	if (!(depths = calc_depths(str, &new_depths)))
		return (ft_send("ERROR\n", fd));
	if (cd((char**)&arg, &g_env) >= 0)
		*depths -= new_depths;
	else
		return (ft_send("ERROR\n", fd));
	ft_send("OK\n", fd);
	return (1);
}
