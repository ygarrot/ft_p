/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:34:50 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 15:40:05 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVEUR_H
#define SERVEUR_H

#include "../../libft/includes/libft.h"
#include <sys/select.h>
#include <sys/types.h>

/* read */
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include <unistd.h>

#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>


#define PORT    5556
#define MAXMSG  512
typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_in t_sockaddr_in;


char	*redirect_command(char *command, char *argv[]);
int		make_socket (uint16_t port);
int		init_serveur();
char	*ft_getenv(char **tb, char *str);
void		ft_setenv(char **arg, char ***env);
void	ft_cd(char *argv[], char ***env);
/* int		eval_loop(fd_set active_fd_set, fd_set read_fd_set); */
/* int		handle_new_socket(fd_set active_fd_set); */
/* int		handle_active_socket(fd_set active_fd_set); */
int		read_from_client (int filedes);
extern char **g_env;
#endif
