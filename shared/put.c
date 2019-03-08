/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:24:52 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/08 19:37:17 by ygarrot          ###   ########.fr       */
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
	send(dest, &size, sizeof(int), 0);
	send(dest, str, size, 0);
	return (1);
}

char	*ft_receive_str(int src)
{
	int		len;
	char	*buffer;

	recv(src, &len, sizeof(int), 0);
	if (len <= 0)
		return (NULL);
	buffer = ft_strnew(len);
	recv(src, buffer, len, 0);
	return (buffer);
}

int		ft_receive(int src, int dest)
{
	char *buffer;

	if (!(buffer = ft_receive_str(src)))
		return (1);
	ft_putstr_fd(buffer, dest);
	ft_memdel((void**)&buffer);
	return (1);
}

int		ft_put(int fd, char **file_name)
{
	struct stat	filestat;
	int			new_fd;

	new_fd = open(file_name[1], O_RDONLY);
	if (new_fd < 0 || is_directory(new_fd)
			|| fstat(new_fd, &filestat) < 0)
	{
		ft_printf("{boldred} [ ERROR ]{reset} %s\n", file_name[1]);
		ft_putendl_fd(OPEN_ERROR, STDERR_FILENO);
		ft_putstr_fd(REQUEST_ERROR, fd);
		return (1);
	}
	ft_putstr_fd(REQUEST_OK, fd);
	ft_printf("{boldgreen} [ SUCCESS ]{reset} sent %s\n", file_name[1]);
	send_file(new_fd, fd, filestat.st_size);
	close(new_fd);
	return (1);
}
