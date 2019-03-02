/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:50:23 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 15:55:53 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

int	read_loop(char *addr, int port)
{
	int sock;
	char *line;

	while(get_next_line(1, &line) >0)
	{
		ft_printf(line);
		sock = create_client(addr, port);
	}
	close(sock);
	return 0;
}
