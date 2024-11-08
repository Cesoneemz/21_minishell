/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 05:07:05 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/05 16:08:46 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(t_env *env, char *key)
{
	t_env	*temp;

	if (!env || !key)
		return (NULL);
	temp = env;
	while (temp)
	{
		if (!ft_strncmp(temp->key, key, ft_strlen(key) + 1))
			return (temp->value);
		temp = temp->next;
	}
	free(temp);
	return (NULL);
}

static void	ft_free_split(char **split)
{
	int	index;

	if (!split)
		return ;
	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}

void	ft_init_env_misc(t_env **env)
{
	int		shlvl;
	char	*shell;

	shell = ft_get_env((*env), "SHLVL");
	shlvl = 1;
	if (shell)
		shlvl = ft_atoi(shell);
	ft_set_env(env, "SHLVL", ft_itoa(++shlvl));
	ft_set_env(env, "PWD", (char *)getcwd(NULL, 0));
}

char	**ft_split_env_var(char **envp, int index)
{
	char	**split_content;

	split_content = ft_split(envp[index], '=');
	if (!split_content)
	{
		perror("Corrupted env");
		exit(errno);
	}
	return (split_content);
}

t_env	*ft_init_env(char **envp)
{
	int		index;
	char	**split_content;
	t_env	*env;
	t_env	*head;

	index = 0;
	env = ft_init_env_node();
	head = env;
	while (envp[index] != NULL)
	{
		split_content = ft_split_env_var(envp, index);
		env->key = ft_strdup(split_content[0]);
		if (split_content[1])
			env->value = ft_strdup(split_content[1]);
		ft_free_split(split_content);
		if (envp[index + 1] == NULL)
			break ;
		env->next = ft_init_env_node();
		env = env->next;
		index++;
	}
	env = head;
	ft_init_env_misc(&env);
	return (env);
}
