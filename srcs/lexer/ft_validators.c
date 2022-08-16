#include "minishell.h"

static int	ft_parse_quote(char *str, char c)
{
	int	index;

	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
		{
			index++;
			while (str[index] != c && str[index] != '\0')
				index++;
			if (str[index] == '\0')
			{
				ft_print_error("parse error");
				return (0);
			}
		}
		index++;
	}
	return (1);
}

int	ft_check_quotes(char *str)
{
	if (!ft_parse_quote(str, '\"') || (!ft_parse_quote(str, '\'')))
		return (0);
	return (1);
}
