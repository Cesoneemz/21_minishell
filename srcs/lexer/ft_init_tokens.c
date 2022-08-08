#include "minishell.h"

t_tokens	*ft_new_token(void)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->value = NULL;
	tokens->next = NULL;
	tokens->type = 0;
	return (tokens);
}