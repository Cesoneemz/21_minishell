#include "minishell.h"

void	ft_free_tokens(t_tokens *tokens)
{
	t_tokens	*temp;

	while (temp != NULL)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}