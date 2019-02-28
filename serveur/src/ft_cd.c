/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 11:10:57 by ygarrot           #+#    #+#             */
/*   Updated: 2019/02/28 15:43:15 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "serveur.h"

void	change_dir(char *arg, char ***env,char is_old)
{
	char	path[256];
	char	**new_oldpwd;
	char	*current;
	char	*oldpwd;

	getcwd(path, 256);
	if (!(current = ft_strdup(path)))
		return;
	oldpwd = ft_getenv(*env, "OLDPWD");
	if (chdir(is_old ? oldpwd : arg) && arg)
	{
		ft_printf("cd : no such file or directory : %s\n", arg);
		return ;
	}
	getcwd(path, 256);
	new_oldpwd = (char*[3]){"", "OLDPWD", current};
	/* tab = (char*[2][256]){{"OLDPWD", current}, {"PWD", path}}; */
	ft_setenv(new_oldpwd, env);
	/* ft_setenv(&tab[1], env); */
}

void	ft_cd(char *argv[], char ***env)
{
	char	*temp;
	char	is_old;
	char	i;

	is_old = !ft_strcmp(argv[0], "-");
	if (!argv[0] || !(i = ft_strcmp(argv[0], "~")))
	{
		if ((temp = ft_getenv(*env, "HOME")))
			change_dir(temp, env, is_old);
		else
			ft_printf("cd : no such file or directory\n");
	}
	else
		change_dir(argv[0], env, is_old);
}
