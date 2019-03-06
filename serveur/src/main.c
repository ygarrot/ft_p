/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 18:11:40 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char **g_env;

int	main(int ac, char *av[], char **env)
{
	char **args;

	if (ac < 2)
	{
		ft_printf("Please give me a port\n");
		return (1);
	}
	if (!ft_getenv(g_env, "PWD"))
		return (ft_printf("%s\n", NO_PWD));
	g_env = ft_strtabdup(env);
	args = (char*[4]){"", "HOME", ft_getenv(g_env, "PWD"), NULL};
	ft_setenv(args, &g_env);
	init_serveur(ac < 3 ? "127.0.0.1" : av[2], ft_atoi(av[1]));
	ft_free_dblechar_tab(g_env);
	return (0);
}
