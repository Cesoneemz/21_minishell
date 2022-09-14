#include "minishell.h"

int	ft_get_len_of_token(char *str, int index, t_tokens *tokens)
{
	while (str[index] != ' ' && str[index] != '\0')
	{
		if (str[index] == '<' || str[index] == '>')
			break ;
		if (str[index] == ' ')
			break ;
		if (str[index] == '|')
			break ;
		tokens->len++;
		index++;
	}
	return (tokens->len);
}