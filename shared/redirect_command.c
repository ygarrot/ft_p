/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:47:40 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/04 13:47:42 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

char	*wait_command(int fd[2], char *command, char **argv)
{
	while ((dup2(fd[1], STDOUT_FILENO) == ERROR_CODE))
		;
	if (close(fd[1]) < 0)
		ft_putendl_fd(CLOSE_ERR, STDERR_FILENO);
	if (close(fd[0]) < 0)
		ft_putendl_fd(CLOSE_ERR, STDERR_FILENO);
	if (execv(command, argv) < 0)
		ft_putendl_fd(EXECV_ERR, STDERR_FILENO);
	exit(1);
}

char	*get_command_output(char *command, char *argv[])
{
	int		filedes[2];
	int		nbytes;
	pid_t	pid;
	char	foo[4096];

	if (pipe(filedes) == ERROR_CODE)
		ft_exit(PIPE_ERR, 1);
	if ((pid = fork()) == ERROR_CODE)
		ft_exit(FORK_ERR, 1);
	else if (!pid)
		wait_command(filedes, command, argv);
	else
	{
		if (close(filedes[1]) == ERROR_CODE)
			ft_putendl_fd(CLOSE_ERR, STDERR_FILENO);
		if ((nbytes = read(filedes[0], foo, sizeof(foo))) < 0)
			return (NULL);
		foo[nbytes] = '\0';
		return (ft_strdup(foo));
	}
	return (NULL);
}

int		redirect_command(char *command, char *argv[], int fd)
{
	char *buffer;

	buffer = get_command_output(command, argv);
	if (!buffer)
		return (ft_send(OOM_DEVICE, fd));
	if (fd != 1)
		ft_send(buffer, fd);
	else
		ft_printf(buffer, fd);
	ft_memdel((void**)&buffer);
	return (0);
}
