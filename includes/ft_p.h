
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serveur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:34:50 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 11:24:46 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_P_H
#define FT_P_H

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

#define MAXMSG  512
typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_in t_sockaddr_in;

typedef struct s_func_dic
{
	char *name;
	int	(*function)(int fd, char *string);
}				t_func_dic;

int		ft_fdcpy(int src, int dest);
char	*redirect_command(char *command, char *argv[]);
int		make_socket (uint16_t port);
int		init_serveur(int port);
char	*ft_getenv(char **tb, char *str);
void	ft_setenv(char **arg, char ***env);

int		ft_cd(char *argv[], char ***env);
int		ft_get(int fd, char *file_name);
int		ft_put(int fd, char *file_name);
int		ft_pwd(int fd, char *file_name);
int		ft_quit(int fd, char *file_name);
int		ft_ls(int fd, char *file_name);

extern char **g_env;
#endif
