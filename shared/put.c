/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:26:43 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 13:18:19 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/* in our case src is client and dest is server */
/* from src : GET __FILE__ */
/* from dest : __FILE__ content line by line */
/* to server: GET */
#define buff_size 0

int		ft_fdcpy(int src, int dest)
{
	int		ret;
	char	buf[buff_size];

	while ((ret = read(src, buf, buff_size)) > 0)
		write(dest, buf, ret);
	return (ret);
}

int		ft_put(int fd, char *file_name)
{
	int new_file_fd;

	if ((new_file_fd = open(file_name, O_RDWR | O_CREAT, S_IRWXU)) < 0)
		return (EXIT_FAILURE);
	ft_fdcpy(fd, new_file_fd);
	if (close(new_file_fd) < -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
