/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:18:17 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 13:54:16 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/* from src: PUT __FILE__ NEW_LINE */
/* __FILE__ content */


int		ft_get(int fd, char *file_name)
{
	/* int depths; */
	int	new_file_fd;

	/* if (!calc_depths(file_name, &depths)) */
		/* return (ft_send("ERROR\n", fd)); */
	if ((new_file_fd = open(file_name, O_WRONLY | O_CREAT, S_IRWXU)) < 0)
		return (EXIT_FAILURE);
	ft_receive(fd, new_file_fd);
	if (close(new_file_fd) < -1)
		return (EXIT_FAILURE);
	return (EXIT_FAILURE);
}
