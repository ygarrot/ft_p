/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:24:52 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/04 13:41:24 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/*
** in our case src is client and dest is server
** from src : GET __FILE__
** from dest : __FILE__ content line by line
** to server: GET
*/

int		ft_send(char *str, int dest)
{
	size_t size;

	size = ft_strlen(str);
	if (send(dest, &size, sizeof(int), 0) == ERROR_CODE)
		ft_putstr_fd(SEND_ERROR, STDERR_FILENO);
	if (send(dest, str, size, 0) == ERROR_CODE)
		ft_putstr_fd(SEND_ERROR, STDERR_FILENO);
	return (1);
}

char	*ft_receive_str(int src)
{
	int		len;
	char	*buffer;

	if (recv(src, &len, sizeof(int), 0) == ERROR_CODE)
		ft_putstr_fd(RECV_ERROR, STDERR_FILENO);
	if (!(buffer = ft_strnew(len)))
		return (NULL);
	if (!(recv(src, buffer, len, 0)))
		ft_putstr_fd(RECV_ERROR, STDERR_FILENO);
	return (buffer);
}

int		ft_receive(int src, int dest)
{
	char *buffer;

	ft_putstr_fd(buffer = ft_receive_str(src), dest);
	ft_memdel((void**)&buffer);
	return (1);
}

int		ft_fdcpy(int src, int dest)
{
	int		ret;
	char	buf[buff_size];

	while ((ret = read(src, buf, buff_size)) > 0)
	{
		if (write(dest, buf, ret) == ERROR_CODE)
			ft_putstr_fd(WRITE_ERROR, STDERR_FILENO);
	}
	return (ret);
}

int		ft_put(int fd, char **file_name)
{
	int		depths;
	char	*file;

	if (!calc_depths(file_name[1], &depths))
		return (ft_send(NACCESS_PARENT, fd));
	file = mmap_file(file_name[1], O_RDONLY);
	if (!file)
		return (ft_send(FILE_DOESNT_EXIST, fd));
	ft_send(REQUEST_OK, fd);
	ft_send(file, fd);
	return (1);
}
