/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:26:43 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 19:11:01 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

/* in our case src is client and dest is server */
/* from src : GET __FILE__ */
/* from dest : __FILE__ content line by line */
/* to server: GET */
#define buff_size 42 

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
	int len;
	char *buffer;

	recv(src, &len, sizeof(int), 0);
	/* len = 42; */
	buffer = ft_strnew(len);
	recv(src, buffer, len, 0);
	return (buffer);
}

int	ft_receive(int src, int dest)
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
		write(dest, buf, ret);
	}
	return (ret);
}

int		ft_put(int fd, char **file_name)
{
	int depths;
	char *file;

	if (!calc_depths(file_name[1], &depths))
		return (ft_send("ERROR cannot access to parents\n", fd));
	file = mmap_file(file_name[1], O_RDONLY);
	if (!file)
		return (ft_send("ERROR no such file\n", fd));
	ft_send("OK\n", fd);
	ft_send(file, fd);
	return (1);
}
