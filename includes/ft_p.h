
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

/* mmap */
#include <sys/mman.h>

#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

/* mmap */ 
#include <sys/mman.h>

#define MAXMSG  512
/* 500 "Requested action not taken. File unavailable (e.g., file not found, no access)." */
#define SEND_ERROR "SEND ERROR"
#define RECV_ERROR "RECV ERROR"
#define WRITE_ERROR "WRITE ERROR"
#define READ_ERROR "READ ERROR"
#define FILE_DOESNT_EXIST "ERROR no such file\n"
#define NACCESS_PARENT "ERROR cannot access to parents\n"
#define REQUEST_OK "OK\n"
#define REQUEST_ERROR "ERROR\n"
#define CLOSE_ERROR "ERROR ON CLOSE"
#define OPEN_ERROR "NO SUCH FILE OR DIRECTORY\n"
#define OOM_DEVICE "NO SPACE LEFT ON DEVICE\n"
#define buff_size 42
#define PIPE_ERR "ERROR ON PIPE"
#define FORK_ERR "ERROR ON FORK"
#define CLOSE_ERR "ERROR ON CLOSE"
#define EXECV_ERR "ERROR ON EXECV"
#define READ_ERR "ERROR ON READ"
#define LS_PATH "/bin/ls"
#define PWD_PATH "/bin/pwd"
#define MKDIR_PATH "/bin/mkdir"
#define RMDIR_PATH "/bin/rmdir"
#define UNLINK_PATH "/bin/unlink"
#define ERROR_CODE -1

typedef struct sockaddr t_sockaddr;
typedef struct sockaddr_in t_sockaddr_in;

typedef enum e_command
{
	CD,
	GET,
	PUT,
	LS,
	PWD,
	QUIT,
	MKDIR,
	RMDIR,
	UNLINK,
	CMD_NBR
}			t_command;

typedef struct s_func_dic
{
	char *name;
	int	(*function)(int fd, char **string);
}				t_func_dic;
int		ft_socketcpy(int src, int dest);

int	ft_exit(char *str, int code);
int *calc_depths(char *str, int *new_depths);
char	*get_command_output(char *command, char*argv[]);
int (*get_cmd(char *cmd, t_func_dic *ft))(int fd, char **arg);
int		redirect_command(char *command, char *argv[], int fd);
int		ft_fdcpy(int src, int dest);
int		make_socket (uint16_t port);
int		init_serveur(int port);
char	*ft_getenv(char **tb, char *str);
void	ft_setenv(char **arg, char ***env);
int	handle_command(int fd, char *str, t_func_dic *dic);
int	ft_receive(int src, int dest);
char	*ft_receive_str(int src);
int		ft_send(char *str, int dest);

int		cd(char *argv[], char ***env);

char	*mmap_file(char *file, int flag);
int		ft_cd(int fd, char **argv);

int		ft_cd(int fd, char **argv);
int		ft_get(int fd, char **argv);
int		ft_put(int fd, char **argv);
int		ft_pwd(int fd, char **argv);
int		ft_quit(int fd, char **argv);
int		ft_ls(int fd, char **argv);
int		ft_mkdir(int fd, char **argv);
int		ft_rmdir(int fd, char **argv);
int		ft_unlink(int fd, char **argv);

extern char **g_env;
#endif
