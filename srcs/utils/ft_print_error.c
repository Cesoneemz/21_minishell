#include "minishell.h"

void	ft_print_error(char *message)
{
	if (message)
		perror(ft_strjoin("minishell: ", message));
}
