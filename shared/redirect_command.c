/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:14:09 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/02 19:32:05 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*get_command_output(char *command, char*argv[])
{
	int filedes[2];
	int nbytes;
	pid_t	pid;
	char foo[4096];

	if (pipe(filedes) == -1) {
		ft_printf("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1) {
		ft_printf("fork");
		exit(1);
	} else if (pid == 0) {
		while ((dup2(filedes[1], STDOUT_FILENO) == -1)) {}
		close(filedes[1]);
		close(filedes[0]);
		execv(command, argv);
		exit(1);
	}else{
		close(filedes[1]);
		nbytes = read(filedes[0], foo, sizeof(foo));
		foo[nbytes] = '\0';
		return (ft_strdup(foo));
	}
	return NULL;
}

int	redirect_command(char *command, char *argv[], int fd)
{
	char *buffer;
	char *tmp[2] = {command, NULL};

	(void)argv;
	buffer = get_command_output(command, tmp);
	ft_send(buffer, fd);
	ft_memdel((void**)&buffer);
	return (0);
}
