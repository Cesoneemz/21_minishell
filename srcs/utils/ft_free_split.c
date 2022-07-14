#include "minishell.h"

void	ft_free_split(char **split)
{
	int	index;

	if (!split)
		return ;
	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}