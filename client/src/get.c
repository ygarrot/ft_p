/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:18:17 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 17:50:17 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

int		get(int fd, char *file_name)
{
	
	if ((ptr = mmap(0, buf.st_size,
					PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (NULL);
	new_file = open(file_name, O_WRONLY);
	write(new_file, ptr, ft_strlen(ptr));
	ft_memdel((void**)&ptr);
}

int		get_v1(char *str)
{
	char **arg = {str, NULL};
	redirect_command("/bin/echo", arg);
}
