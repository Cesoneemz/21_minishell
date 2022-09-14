#include "minishell.h"

int	ft_init_cmd(t_info *info, t_tokens *tokens)
{
	t_tokens	*temp;
	int			index;

	info->cmd_count = ft_count_cmd(tokens);
	if (info->cmd_count == -1)
		return (-1);
	info->cmd_list = (t_cmd *)malloc(info->cmd_count * sizeof(t_cmd));
	if (!info->cmd_list)
		return (-1);
	return (1);
}

char	*ft_parse_cmd(char *cmd, t_token_types type, t_info *info)
{
	int			index;

	index = 0;
	if (type == EXP_FIELD)
		return (ft_quotes_treatment(cmd, type, info));
	while (cmd[index] != '\0' && type != FIELD)
	{
		if (cmd[index] == '$')
			return (ft_dollar_treatment(cmd, info, index));
		index++;
	}
	return (cmd);
}

char	**ft_parse_args(t_tokens **tokens, t_info *info)
{
	int		args_count;
	char	**args;
	int		index;

	args_count = ft_count_args(*tokens);
	args = (char **)malloc((args_count + 1) * sizeof(char *));
	if (!args)
		return (NULL);
	ft_memset(args, '\0', (args_count + 1) * sizeof(char *));
	index = 0;
	while (index < args_count)
	{
		if ((*tokens)->type != SEP)
		{
			args[index] = ft_strdup(ft_parse_cmd((*tokens)->value, (*tokens)->type, info));
			index++;
		}
		(*tokens) = (*tokens)->next;
	}
	args[index] = NULL;
	while (*tokens != NULL && (*tokens)->type == SEP)
		(*tokens) = (*tokens)->next;
	return (args);
}

int	ft_create_cmd(t_info *info, t_tokens **tokens, int index)
{
	while ((*tokens)->type == SEP)
		(*tokens) = (*tokens)->next;
	info->cmd_list[index].cmd = ft_parse_cmd(ft_strdup((*tokens)->value), (*tokens)->type, info);
	(*tokens) = (*tokens)->next;
	info->cmd_list[index].args = ft_parse_args(tokens, info);
	return (0);
}


