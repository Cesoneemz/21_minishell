#include "minishell.h"

void	ft_print_error(char *message)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(message, 1);
	ft_putstr_fd("\n", 1);
}