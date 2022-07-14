#include "minishell.h"

t_env	*ft_get_env(t_env *env, char *var)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, var, ft_strlen(var)))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}