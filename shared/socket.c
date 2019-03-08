/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 16:20:17 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/08 19:36:29 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		send_file(int src, int dest, size_t size)
{
	char	*buffer;
	int		curr_size;
	int		i;

	ft_putendl_fd("serveur", dest);
	ft_putendl_fd("", dest);
	buffer = ft_strnew(size + 1);
	send(dest, &size, sizeof(long), 0);
	read(src, buffer, size);
	curr_size = size;
	i = 0;
	while (size > 0)
	{
		curr_size = size < BUFF_S ? size : BUFF_S;
		send(dest, &buffer[i], curr_size * sizeof(char), 0);
		i += curr_size;
		size -= curr_size;
	}
	ft_memdel((void**)&buffer);
	return (1);
}

int		ft_fdcpy(int src, int dest, size_t buff_size)
{
	int		ret;
	char	buf[buff_size];

	ret = read(src, buf, buff_size);
	write(dest, buf, ret);
	return (ret);
}

int		receive_file(int src, int dst, int nc)
{
	long	len;
	char	*buffer;
	long	t_len;
	int		current;
	int		i;

	if (!nc && (recv(src, (void*)&len, sizeof(long), 0) <= 0))
		return (-ft_printf("Error\n"));
	len = nc ? nc : len;
	t_len = len;
	if (!(buffer = ft_strnew(len + 1)))
		ft_exit(OOM_DEVICE, EXIT_FAILURE);
	i = 0;
	while (len > 0)
	{
		current = len > BUFF_S ? BUFF_S : len;
		recv(src, &buffer[i], current * sizeof(char), 0);
		len -= BUFF_S;
		i += current;
	}
	write(dst, buffer, t_len);
	ft_memdel((void**)&buffer);
	return (1);
}
