/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:42:13 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 19:17:40 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		ft_mkdir(int fd, char **str)
{
	(void)str;
	return (redirect_command("/bin/mkdir",str, fd));
}

int		ft_rmdir(int fd, char **str)
{
	(void)str;
	return (redirect_command("/bin/rmdir", str, fd));
}

int		ft_unlink(int fd, char **str)
{
	(void)str;
	return (redirect_command("/bin/unlink",str, fd));
}
