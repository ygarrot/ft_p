/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:18:17 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 19:11:32 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/* from src: PUT __FILE__ NEW_LINE */
/* __FILE__ content */


int		ft_get(int fd, char **file_name)
{
	int		new_file_fd;
	int		i;
	char *to_del;

	to_del = ft_receive_str(fd);
	if (!to_del || ft_strncmp(to_del, "OK", 2))
	{
		ft_memdel((void**)&to_del);
		return (EXIT_FAILURE);
	}
	ft_memdel((void**)&to_del);
	i = ft_strlen(file_name[1]);
	while (i > 0 && file_name[1][i] != '/')
		i--;
	i = i ? i + 1  : i;
	if ((new_file_fd = open(&file_name[1][i], O_WRONLY | O_CREAT, S_IRWXU)) < 0)
		return (ft_printf("%s\n", OPEN_ERROR));
	ft_receive(fd, new_file_fd);
	if (close(new_file_fd) < -1)
		return (ft_printf("%s\n", CLOSE_ERROR));
	return (EXIT_SUCCESS);
}
