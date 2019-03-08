/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:18:17 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/08 19:40:18 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** from src: PUT __FILE__ NEW_LINE
** __FILE__ content
*/

int			handle_netcat(int fd, int file)
{
	char	*buffer;
	long	len;

	if (get_next_line(fd, &buffer) <= 0)
		return (1);
	len = 0;
	if (ft_strcmp(buffer, "client"))
	{
		ft_memdel((void**)&buffer);
		get_next_line(fd, &buffer);
		len = ft_atoi(buffer);
	}
	ft_memdel((void**)&buffer);
	receive_file(fd, file, len);
	return (1);
}

static int	len_r(char *str)
{
	int		i;

	i = ft_strlen(str);
	while (i > 0 && str[i] != '/')
		i--;
	return (i ? i + 1 : i);
}

int			ft_get(int fd, char **file_name)
{
	int		file_fd;
	char	*to_del;

	to_del = NULL;
	if (get_next_line(fd, &to_del) <= 0 ||
		!to_del || ft_strncmp(to_del, "OK", 2))
	{
		ft_printf("{boldred} [ ERROR ]{reset} get %s\n", file_name[1]);
		ft_memdel((void**)&to_del);
		return (EXIT_SUCCESS);
	}
	ft_memdel((void**)&to_del);
	if ((file_fd = open(&file_name[1][len_r(file_name[1])],
		O_SYNC | O_WRONLY | O_CREAT, S_IRWXU))
		== ERROR_CODE)
	{
		ft_printf("{boldred} [ ERROR ]{reset} %s\n", file_name[1]);
		return (EXIT_SUCCESS);
	}
	ft_printf("SUCCESS received %s\n", file_name[1]);
	handle_netcat(fd, file_fd);
	if (close(file_fd) == ERROR_CODE)
		ft_putendl_fd(CLOSE_ERROR, STDERR_FILENO);
	return (EXIT_SUCCESS);
}
