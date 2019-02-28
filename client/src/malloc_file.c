/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 16:29:51 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 17:46:19 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char	*mmap_file(char *file)
{
	int			ret;
	int			fd;
	char		*ptr;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (NULL);
	if (fstat(fd, &buf) < 0)
		return (NULL);
	if (is_directory(fd))
		return (NULL);
	if ((ptr = mmap(0, buf.st_size,
					PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NULL);
	return (ptr);
}
