/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:24:52 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/07 15:16:05 by ygarrot          ###   ########.fr       */
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
	int		i;
	int		n;
	char	*to_del;

	i = -1;
	n = 0;
	while (str[++i])
		if (str[i] == '\n')
			n++;
	if (!(to_del = ft_itoa(n)))
		return (ERROR_CODE);
	ft_putendl_fd(to_del, dest);
	ft_memdel((void**)&to_del);
	ft_putendl_fd(str, dest);
	return (0);
}

char	*ft_receive_str(int src)
{
	char	*tmp;
	char	*buffer;
	int		nb;

	tmp = ft_memalloc(1);
	if (get_next_line(src, &buffer) <= 0)
		return (NULL);
	nb = ft_atoi(buffer) + 1;
	ft_memdel((void**)&buffer);
	while (nb-- > 0)
	{
		if (get_next_line(src, &buffer) <= 0)
			return (tmp);
		tmp = ft_realloc(tmp, ft_strlen(tmp) + ft_strlen(buffer) + 2);
		ft_strcat(tmp, buffer);
		ft_memdel((void**)&buffer);
		if (nb - 1)
			ft_strcat(tmp, "\n");
	}
	return (tmp);
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
	char	*file;

	file = mmap_file(file_name[1], O_RDONLY);
	if (!file)
	{
		ft_putendl_fd(FILE_DOESNT_EXIST, 1);
		ft_putendl_fd(FILE_DOESNT_EXIST, fd);
		return (1);
	}
	ft_putendl_fd(REQUEST_OK, fd);
	ft_send(file, fd);
	return (1);
}
