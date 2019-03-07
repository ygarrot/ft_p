/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 15:42:04 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/07 12:58:27 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

char **g_env;

int	main(int ac, char *av[], char **env)
{
	int		depth;
	int		*last;
	char	**args;

	if (ac < 2)
	{
		ft_printf("Please give me a port\n");
		return (1);
	}
	g_env = ft_strtabdup(env);
	if (!ft_getenv(g_env, "PWD"))
		return (ft_printf("%s\n", NO_PWD));
	args = (char*[4]){"", "HOME", ft_getenv(g_env, "PWD"), NULL};
	ft_setenv(args, &g_env);
	init_serveur(ac < 3 ? "127.0.0.1" : av[2], ft_atoi(av[1]));
	ft_free_dblechar_tab(g_env);
	last = calc_depths(&ft_getenv(g_env, "PWD")
	[ft_strlen(ft_getenv(g_env, "HOME"))], &depth, 1);
	*last = -depth;
	return (0);
}
