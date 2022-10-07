/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 20:39:07 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/05 16:14:34 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executer.h"

int	ft_built_env(char **arglist, t_env *env)
{
	char	**env_list;

	(void) arglist;
	//print_env_tokens(env);
	env_list = make_env_list(env);
	//printf("\t+-=-=-=-=-=-=-=-=s\n");
	while (*env_list)
	{
		write(1, *env_list, ft_strlen(*env_list));
		write(1, "\n", 1);
		env_list++;
	}
	//printf("\t%s\n", *env_list++);
	//printf("\t+-=-=-=-=-=-=-=-=s\n");
	return (0);
}

int	ft_export_env(char **arglist, t_env *env)
{
	char	**keyval;
	t_env	*new_env;
	t_env	*last;

	keyval = ft_split(arglist[1], '=');
	printf("   __ft_export_env: %s = %s \n", keyval[0], keyval[1]);
	if (ft_get_env(env, keyval[0]) != NULL)
		ft_set_env(&env, keyval[0], keyval[1]);
	else
	{
		new_env = ft_lstnew_env(keyval[0], keyval[1]);
		last = ft_lstlast_env(env);
		last->next = new_env;
	}
	printf("   __ft_get_env: %s \n", ft_get_env(env, keyval[0]));
	return (0);
}

static int	ft_lstdelete_env(t_env	*prev, t_env *temp, t_env **env)
{
	if (prev != NULL)
	{
		if (temp->next != NULL)
			prev->next = temp->next;
		else
			prev->next = NULL;
	}
	else
		*env = temp->next;
	free(temp);
	return (0);
}

int	ft_unset_env(char **arglist, t_env **env)
{
	t_env	*prev;
	t_env	*temp;

	if (ft_get_env(*env, arglist[1]) == NULL)
		return (0);
	prev = NULL;
	temp = *env;
	while (temp)
	{
		if (!ft_strncmp(temp->key, arglist[1], ft_strlen(arglist[1]) + 1))
		{
			printf(" ..deleting from list env: %s = %s \n", arglist[1], temp->value);
			return (ft_lstdelete_env(prev, temp, env));
		}
		prev = temp;
		temp = temp->next;
	}
	return (0);
}
