/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 12:08:00 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 12:43:56 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int		ft_exit(char *str, int ret)
{
	/*TODO : toremove*/
	perror(str);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(ret);
}