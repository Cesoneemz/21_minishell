#include "minishell.h"

static t_list	*ft_add_env_to_list(t_list *env, char *envp)
{
	char	**split_content;
	t_env	*key_value;

	key_value = (t_env *)malloc(sizeof(t_env));
	if (!key_value)
		return (NULL);
	split_content = ft_split(envp, '=');
	if (!split_content)
		return (NULL);
	key_value->key = ft_strdup(split_content[0]);
	key_value->value = ft_strdup(getenv(key_value->key));
    ft_lstadd_back(&env, ft_lstnew(key_value));
	free(split_content[0]);
	free(split_content[1]);
	free(key_value->key);
	free(key_value->value);
	free(key_value);
	return (env);
}

char	*ft_get_env(t_list *env, char *key)
{
	t_env	*value;
	t_list	*temp;

	if (!env || !key)
		return (NULL);
	temp = env;
	while (temp)
	{
		value = (t_env *)(temp->content);
		if (!ft_strncmp(value->key, key, ft_strlen(key) + 1))
		{
			free(temp);
			return (value->value);
		}
		temp = temp->next;
	}
	free(temp);
	return (NULL);
}

t_list	*ft_init_env(char **envp)
{
	int		index;
	t_list	*env;

	index = 0;
    env = NULL;
	while (envp[index] && envp)
	{
		env = ft_add_env_to_list(env, envp[index]);
		index++;
	}
	return (env);
}