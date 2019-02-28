/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:26:43 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 17:46:47 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

/* in our case src is client and dest is server */
/* from src : GET __FILE__ */
/* from dest : __FILE__ content line by line */

to server: GET
int		fd_cpy(int src, int dest)
{
	char	buf[BUF_SIZE];

	while ((ret = read(fd, buf, BUF_SIZE)) > 0)
		write(fd, buf, ret);
	return (ret);
}

int		put(int fd, char *file_name)
{
	if ((new_file_fd = open(file_name, O_WRONLY)) < 0)
		return (EXIT_FAILURE);
	ft_fdcpy(fd, new_file_fd);
	if (close(new_file_fd) < -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
