/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 14:47:28 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/04 13:58:30 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int			ft_setenv_new(char ***env, char *str, char *value)
{
	size_t	i;
	size_t	j;
	int		k;
	char	**new;

	i = 0;
	while (env[0][i])
		i++;
	if (!(new = (char**)malloc(sizeof(char*) * (i + 2))))
		return (0);
	i = 0;
	k = 0;
	j = ft_strlen(str);
	while (env[0][i] && (ft_strncmp(env[0][i], str, j) || env[0][i][j] != '='))
		new[k++] = env[0][i++];
	new[i] = value;
	i += !(env[0][i] == 0);
	ft_strdel(&env[0][k]);
	while (env[0][i])
		new[k++ + 1] = env[0][i++];
	new[k + 1] = 0;
	free(*env);
	*env = new;
	return (0);
}

void		ft_setenv(char **arg, char ***env)
{
	char	*value;

	if (!arg || !env || !*env)
		return ;
	else
	{
		if ((value = (char*)malloc(ft_strlen(arg[1]) + ft_strlen(arg[2]) + 2)))
		{
			value[0] = 0;
			ft_strcat(value, arg[1]);
			ft_strcat(value, "=");
			if (arg[2])
				ft_strcat(value, arg[2]);
		}
	}
}
