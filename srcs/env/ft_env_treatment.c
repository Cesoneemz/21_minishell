#include "minishell.h"

static char	*ft_get_env_value(char *str, t_env *env)
{
	char	*result;
	int		index;
	int		var_len;
	char	*var;
	t_env	*env_var;

	index = 0;
	while (str[index] != '$')
		index++;
	var_len = (ft_strclen(str, '=') - index + 1);
	var = ft_substr(str, index + 1, var_len);
	env = ft_get_env(env, var);
	return (env->value);
}

char	*ft_get_env_vars(char *str, t_env *env)
{
	int		dol_dol;
	int		len;
	int		index;
	char	*env_value;

	if (ft_strchr(str, '$') < 0)
		return (str);
	dol_dol = 0;
	len = ft_strlen(str);
	if (len >= 2 && str[len - 1] == '$' && str[len - 2] != '$')
		dol_dol = 1;
	while (str[index] != '\0')
	{
		if (str[index] == '$')
		{
			env_value = ft_get_env_value(str, env);
		}
	}
	if (!result)
		return (NULL);
	return (result);
}