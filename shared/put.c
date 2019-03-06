/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:24:52 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 17:14:51 by ygarrot          ###   ########.fr       */
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

	i = -1;
	n = 0;
	while (str[++i])
		if (str[i] == '\n')
			n++;
	ft_putendl_fd(ft_itoa(n), dest);
	ft_putendl_fd(str, dest);
	return (1);
}

char	*ft_receive_str(int src)
{
	char	*tmp;
	char	*buffer ;
	int nb;

	tmp = ft_memalloc(1);
	if (get_next_line_b(src, &buffer, 1) <= 0)
		return (NULL);
	nb = ft_atoi(buffer) + 1;
	ft_memdel((void**)&buffer);
	while (nb-- > 0)
	{
		get_next_line_b(src, &buffer, 1);
		tmp = ft_realloc(tmp, ft_strlen(tmp) + ft_strlen(buffer) + 2);
		ft_strcat(tmp, buffer);
		if (nb - 1)
			ft_strcat(tmp, "\n");
	}
	return (tmp);
}

int		ft_receive(int src, int dest)
{
	char *buffer;

	ft_putstr_fd(buffer = ft_receive_str(src), dest);
	ft_memdel((void**)&buffer);
	return (1);
}

int		ft_fdcpy2(int src, int dest, size_t buff_size)
{
	int		ret;
	char	buf[buff_size + 1];

	if (0 > (ret = read(src, buf, buff_size)))
		return (0);
	if (write(dest, buf, ret) == ERROR_CODE)
		ft_putstr_fd(WRITE_ERROR, STDERR_FILENO);
	return (ret);
}

int		ft_fdcpy(int src, int dest, size_t buff_size)
{
	int		ret;
	char	buf[buff_size + 1];

	while ((ret = read(src, buf, buff_size)) > 0)
	{
		if (write(dest, buf, ret) == ERROR_CODE)
			ft_putstr_fd(WRITE_ERROR, STDERR_FILENO);
	}
	return (ret);
}

int		ft_put(int fd, char **file_name)
{
	char	*file;

	file = mmap_file(file_name[1], O_RDONLY);
	if (!file)
		return (ft_send(FILE_DOESNT_EXIST, fd));
	ft_putendl_fd(REQUEST_OK, fd);
	ft_send(file, fd);
	return (1);
}
