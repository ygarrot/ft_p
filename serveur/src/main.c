/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/05 13:34:22 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char **g_env;

int main(int ac, char *av[], char **env)
{
	(void)ac;(void)av;(void)env;
	if (ac < 2)
	{
		ft_printf("Please give me a port\n");
		return 1;
	}
	g_env = env;
	init_serveur(ac < 3 ? "127.0.0.1" : av[2], ft_atoi(av[1]));
	return 0;
}
