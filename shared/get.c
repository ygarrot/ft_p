/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:18:17 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 19:04:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** from src: PUT __FILE__ NEW_LINE
** __FILE__ content
*/

int		ft_get(int fd, char **file_name)
{
	int		file_fd;
	int		i;
	char	*to_del;

	get_next_line_b(fd, &to_del, 1);
	if (!to_del || ft_strncmp(to_del, "OK", 2))
	{
		ft_memdel((void**)&to_del);
		return (ERROR_CODE);
	}
	ft_memdel((void**)&to_del);
	i = ft_strlen(file_name[1]);
	while (i > 0 && file_name[1][i] != '/')
		i--;
	i = i ? i + 1 : i;
	if ((file_fd = open(&file_name[1][i], O_WRONLY | O_CREAT, S_IRWXU))
		== ERROR_CODE)
	{
		ft_putendl_fd(OPEN_ERROR, STDERR_FILENO);
		return (ERROR_CODE);
	}
	ft_receive(fd, file_fd);
	if (close(file_fd) < -1)
		ft_putendl_fd(CLOSE_ERROR, STDERR_FILENO);
	return (EXIT_SUCCESS);
}
