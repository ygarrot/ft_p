/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:23:43 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 14:57:12 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*ft_getenv(char **tb, char *str)
{
	int	len;

	if (!tb || !str)
		return (NULL);
	len = ft_strlen(str);
	while (*tb && (ft_strncmp(*tb, str, len) || tb[0][len] != '='))
		tb++;
	return (&tb[0][len + 1]);
}

char	**ft_strtabdup(char **tb)
{
	char	**dup;
	int		i;

	if (!tb)
		return (NULL);
	i = 0;
	while (tb[i])
		i++;
	if (!(dup = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (tb[i])
	{
		if (!(dup[i] = ft_strdup(tb[i])))
		{
			while (i > 0 && --i >= 0)
				free(dup[i]);
			free(dup);
			return (NULL);
		}
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
