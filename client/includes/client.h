/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:51:19 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 11:36:48 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
#define CLIENT_H

#include "../../includes/ft_p.h"

typedef enum e_client_command
{
	LCD,
	LLS,
	LPWD,
	C_COMMAND_NB
}			t_client_command;

#define CLIENT_TAB (char*[3]){ "lcd", "lls", "lpwd"}
#define SERVER_TAB (char*[6]){ "get", "ls", "pwd" , "put", "quit", "cd"}
int	read_loop(char *addr, int port);
int create_client(char *addr, int port);

#endif
