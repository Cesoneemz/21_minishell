#include "minishell.h"

int	ft_strclen(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != c)
		index++;
	return (index);
}