/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 15:23:43 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 17:17:59 by ygarrot          ###   ########.fr       */
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
	return (tb[len + 2]);
}
