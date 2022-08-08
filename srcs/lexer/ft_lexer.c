#include "minishell.h"

static void	ft_get_type_of_token(t_tokens *tokens)
{
	if (strncmp(tokens->value, ">", 1) == 0)
		tokens->type = TRUNC;
	if (strncmp(tokens->value, "<", 1) == 0)
		tokens->type = INPUT;
	if (strncmp(tokens->value, ">>", 1) == 0)
		tokens->type = APPEND;
	if (strncmp(tokens->value, "<<", 1) == 0)
		tokens->type = HEREDOC;
	if (strncmp(tokens->value, "|", 1) == 0)
		tokens->type = PIPE;
	if (tokens->type == 0)
		tokens->type = WORD;
}

void	ft_lexer(char *str, t_tokens *tokens)
{
	int			len;
	int			index;
	int			temp;

	len = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (!ft_is_space(str[index]))
		{
			if (!ft_check_quotes(str))
				return ;
			temp = index;
			len = 0;
			while (!ft_is_space(str[index]) && str[index] != '\0')
			{
				len++;
				index++;
			}
			tokens->value = ft_substr(str, temp, len);
			ft_get_type_of_token(tokens);
			if (str[index + 1] != '\0')
			{
				tokens->next = ft_new_token();
				tokens = tokens->next;
			}
		}
		index++;
	}
}