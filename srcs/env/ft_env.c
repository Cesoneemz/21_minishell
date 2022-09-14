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
	key_value->key = split_content[0];
	key_value->value = split_content[1];
	ft_lstadd_back(&env, ft_lstnew(key_value));
	free(split_content);
	return (env);
}

char	*ft_get_env(t_list *env, char *key)
{
	t_env	*value;

	if (!env || !key)
		return (NULL);
	while (env)
	{
		value = (t_env *)(env->content);
		if (!ft_strncmp(value->key, key, ft_strlen(key) + 1))
			return (value->value);
		env = env->next;
	}
	return (NULL);
}

t_list	*ft_init_env(char **envp)
{
	int		index;
	t_list	*env;

	index = 0;
	env = NULL;
	while (envp && envp[index])
	{
		env = ft_add_env_to_list(env, envp[index]);
		index++;
	}
	return (env);
}