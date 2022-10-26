/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:32:00 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/23 15:22:10 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	env_list_count(t_env *tmp_env)
{
	int		c;

	c = 0;
	while (tmp_env)
	{
		c++;
		tmp_env = tmp_env->next;
	}
	return (c);
}

char	**make_env_list(t_env *env)
{
	int		c;
	int		i;
	t_env	*tmp_env;
	char	**env_list;
	char	*tmp;

	c = env_list_count(env);
	tmp_env = env;
	env_list = ft_calloc(c + 1, sizeof(char *));
	env_list[c] = 0;
	tmp = NULL;
	i = 0;
	while (i < c)
	{
		tmp = ft_strjoin(tmp_env->key, "=");
		env_list[i] = ft_strjoin(tmp, tmp_env->value);
		if (tmp)
			free(tmp);
		tmp_env = tmp_env->next;
		i++;
	}
	return (env_list);
}
/*
void	print_env_tokens(t_env *env)
{
	t_env	*tmp_env;

	tmp_env = env;
	printf("\t+-=-=-=-=-=-=-=-=s\n");
	while (tmp_env)
	{
		printf("\t %s = %s\n", tmp_env->key, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	printf("\t+-=-=-=-=-=-=-=-=s\n");
}
*/