/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygarrot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/08 11:10:57 by ygarrot           #+#    #+#             */
/*   Updated: 2019/03/03 15:41:27 by ygarrot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_p.h"

int	change_dir(char *arg, char ***env,char is_old)
{
	char	path[256];
	char	**new_oldpwd;
	char	*current;
	char	*oldpwd;

	getcwd(path, 256);
	if (!(current = ft_strdup(path)))
		return (-1);
	oldpwd = ft_getenv(*env, "OLDPWD");
	if (chdir(is_old ? oldpwd : arg) && arg)
		return (-1);
	getcwd(path, 256);
	new_oldpwd = (char*[3]){"", "OLDPWD", current};
	ft_setenv(new_oldpwd, env);
	new_oldpwd = (char*[3]){"", "PWD", path};
	ft_setenv(new_oldpwd, env);
	return (1);
}

int	cd(char *argv[], char ***env)
{
	char	*temp;
	char	is_old;
	char	i;

	is_old = !ft_strcmp(argv[0], "-");
	if (!argv[0] || !(i = ft_strcmp(argv[0], "~")))
	{
		if ((temp = ft_getenv(*env, "HOME")))
			return (change_dir(temp, env, is_old));
		else
			return (-1);
	}
	else
		return (change_dir(argv[0], env, is_old));
	return (1);
}
