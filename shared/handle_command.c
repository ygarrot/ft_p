/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:36:31 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/07 13:00:44 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** alternate to func dic
*/

int		*calc_depths(char *str, int *new_depths, int is_cd)
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
		{
			++*new_depths;
			if (!is_cd && (depths - *new_depths) < 0)
				return (&depths);
		}
		else if (i > 0 && ft_strncmp(&str[i], "/.", 2)
				&& str[i] == '/' && str[i + 1])
		{
			tmp = ft_strndup(str, i + 1 + ft_strlento(&str[i + 1], '/'));
			if (is_directory_str(tmp) == 1 && (set = 1))
				--*new_depths;
			ft_memdel((void**)&tmp);
		}
	*new_depths = (set ? *new_depths : -1);
	return (&depths);
}

int check_access(char **argv)
{
	int	i;
	int	*depths;
	int	new_depths;

	if (!ft_strcmp(argv[0], "put") || !ft_strcmp(argv[0], "cd"))
		return (1);
	i = 0;
	while (argv[++i])
	{
		if (!(depths = calc_depths(argv[i], &new_depths, 0)) ||
			argv[i][0] == '/' || (*depths - new_depths) < 0)
			return (ERROR_CODE);
	}
	return (1);
}

char	**handle_command(int fd, char *str, t_func_dic *fdic, int is_server)
{
	int		(*ft)(int, char**);
	char	**argv;
	int		isdel;
	int		ret;

	isdel = 0;
	str[ft_strlento(str, '\n')] = '\0';
	if (!(argv = ft_strsplit(str, ' ')))
		return (NULL);
	if (!(ft = get_cmd(argv[0], (t_func_dic*)fdic)))
		return (argv);
	if (is_server && argv[1] && argv[2] && (isdel=1))
		argv[2] = NULL;
	if (is_server && check_access(argv) == ERROR_CODE)
	{
		isdel == 1 ? argv[2] = "" : 0;
		ft_send(NACCESS_PARENT, fd);
		return (argv);
	}
	else
		ret = ft(fd, argv);
	return (argv);
}
