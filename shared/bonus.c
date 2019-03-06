/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 18:42:13 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 17:54:27 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		ft_mkdir(int fd, char **str)
{
	return (redirect_command(MKDIR_PATH, str, fd));
}

int		ft_rmdir(int fd, char **str)
{
	return (redirect_command(RMDIR_PATH, str, fd));
}

int		ft_unlink(int fd, char **str)
{
	return (redirect_command(UNLINK_PATH, str, fd));
}
