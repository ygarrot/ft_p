/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mmap_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 19:09:49 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 17:46:10 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*mmap_file(char *file, int flag)
{
	int			fd;
	char		*ptr;
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
	return (ptr);
}
