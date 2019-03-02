/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:34:50 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 16:01:57 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
#define SERVEUR_H

#include "../../includes/ft_p.h"
const t_func_dic *fdic_server = (t_func_dic[CMD_NBR]){
	{"cd", ft_cd},
	{"ls", ft_ls},
	{"put", ft_get},
	{"get", ft_put},
	{"pwd", ft_pwd},
	/* {"quit", ft_quit} */
};

#endif
