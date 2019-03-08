/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:09:49 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/07 17:25:49 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	*mmap_file(char *file, int flag)
{
	int			fd;
	void		*ptr;
	struct stat	buf;

	if ((fd = open(file, flag)) == ERROR_CODE)
		return (NULL);
	if (fstat(fd, &buf) == ERROR_CODE)
		return (NULL);
	if (is_directory(fd))
		return (NULL);
	if ((ptr = mmap(0, buf.st_size,
					PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED)
		return (NULL);
	close(fd);
	return (ptr);
}
