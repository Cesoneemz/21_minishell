/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:39:07 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/05 16:06:00 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	ft_set_oldpwd(char *key, char *val, t_env *env)
{	
	t_env	*new_env;
	t_env	*last;

	if (ft_get_env(env, key) != NULL)
		ft_set_env(&env, key, val);
	else
	{
		new_env = ft_lstnew_env(key, val);
		last = ft_lstlast_env(env);
		last->next = new_env;
	}	
	return (0);
}

int	ft_cd_prev2(t_env *env)
{
	char	*oldpwd;
	char	*cwd;

	oldpwd = ft_get_env(env, "OLDPWD");
	cwd = getcwd(NULL, 0);
	//printf("\t   cd - OLDPWD: (%s) \t PWD: (%s)\n", oldpwd, cwd);
	if (oldpwd == NULL || chdir(oldpwd) != 0)
	{
		write(1, "-minishell: cd: OLDPWD not set\n", 31);
		return (1);
	}
	ft_set_oldpwd("OLDPWD", cwd, env);
	cwd = getcwd(NULL, 0);
	ft_set_oldpwd("PWD", cwd, env);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	//printf("\t   OLDPWD: (%s) \t PWD: (%s)\n", ft_get_env(env, "OLDPWD"), ft_get_env(env, "PWD"));
	return (0);
}

int	ft_cd_parent2(char **arglist, t_env *env)
{
	char	*cwd;
	char	*path;
	int		i;

	i = 0;
	if (!arglist || !arglist[1])
		return (0);
	if (arglist[1][0] == '-')
		return (ft_cd_prev2(env));
	if (arglist[1][0] == '~')
		path = ft_strjoin(ft_get_env(env, "HOME"), arglist[1] + 1);
	else
		path = arglist[1];
	if (chdir(path) != 0)
	{
		perror(ft_strjoin("cd: ", path));
		return (1);
	}
	cwd = getcwd(NULL, 0);
	//printf("\t   set OLDPWD: (%s) \t PWD: (%s)\n", oldpwd, cwd);
	ft_set_oldpwd("OLDPWD", ft_get_env(env, "PWD"), env);
	ft_set_oldpwd("PWD", cwd, env);
	//printf("\t   OLDPWD: (%s) \t PWD: (%s)\n", ft_get_env(env, "OLDPWD"), ft_get_env(env, "PWD"));
	return (0);
}
