#include "minishell.h"

void	ft_free_tokens(t_tokens *tokens)
{
	t_tokens	*temp;

	temp = tokens;
	while (tokens != NULL)
	{
		free(tokens->value);
		tokens = tokens->next;
	}
	tokens = temp;
	while (tokens != NULL)
	{
		temp = tokens;
		free(tokens);
		tokens = temp->next;
	}
}

void	ft_free_env(void *content)
{
	t_env	*temp;

	temp = (t_env *)content;
	free(content);
}

void	ft_free_info(t_info *info)
{
	int		index;
	int		jndex;
	t_list	*temp;

	index = info->cmd_count;
	while (index--)
	{
		free(info->cmd_list[index].cmd);
		jndex = 0;
		while (info->cmd_list[index].args[jndex])
		{
			free(info->cmd_list[index].args[jndex]);
			jndex++;
		}
	}
	free(info->cmd_list);
	temp = info->env;
	ft_lstiter(info->env, &ft_free_env);
}