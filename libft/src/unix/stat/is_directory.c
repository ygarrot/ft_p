/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 12:22:07 by ygarrot           #+#    #+#             */
/*   Updated: 2019/01/28 19:41:08 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>

int	is_directory(int fd)
{
	struct stat statbuf;

	if (fstat(fd, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
