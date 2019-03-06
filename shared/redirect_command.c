/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 13:47:40 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/06 16:50:14 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

void	wait_command(int fd[2], char *command, char **argv)
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

char *get_command(int filedes[2])
{
	char	*foo;
	char	*tmp;

	if (!(tmp = ft_memalloc(1)))
		return (NULL);
	if (close(filedes[1]) == ERROR_CODE)
		ft_putendl_fd(CLOSE_ERR, STDERR_FILENO);
	while (get_next_line(filedes[0], &foo) > 0)
	{
		if (!(tmp = ft_realloc(tmp, ft_strlen(tmp)
			+ ft_strlen(foo) + 2)))
			return (NULL);
		ft_strcat(tmp, foo);
		ft_strcat(tmp, "\n");
		ft_memdel((void**)&foo);
	}
	tmp[ft_strlen(tmp)] = 0;
	return (tmp);
}

char	*get_command_output(char *command, char *argv[])
{
	int		filedes[2];
	pid_t	pid;

	if (pipe(filedes) == ERROR_CODE)
		ft_exit(PIPE_ERR, 1);
	if ((pid = fork()) == ERROR_CODE)
		ft_exit(FORK_ERR, 1);
	else if (!pid)
		wait_command(filedes, command, argv);
	else
		return (get_command(filedes));
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
