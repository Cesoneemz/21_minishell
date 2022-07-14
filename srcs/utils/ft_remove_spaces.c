#include "minishell.h"

static int	ft_check_in_quotes(char *str, int pos, char quote, char other)
{
	int	count;
	int	count_other;
	int	i;

	if (quote == '"' && ft_check_in_quotes(str, pos, '\'', '"'))
		return (1);
	count = 0;
	count_other = 0;
	i = 0;
	while (i < pos)
	{
		if (str[i] == other && count % 2 == 0)
			count_other++;
		else if (str[i] == quote && count_other % 2 == 0)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	return (1);
}

static int	ft_check_space(char *str, int pos)
{
	if (str[pos] != ' ' || (pos > 0 && str[pos] == ' ' && str[pos - 1] != ' '))
		return (0);
	else if (str[pos] == ' ' && ft_check_in_quotes(str, pos, '"', '\''))
		return (0);
	return (1);
}

char	*ft_remove_spaces(char *str)
{
	int		index;
	int		size;
	char	*result;

	index = 0;
	size = 0;
	while (str[index] != '\0')
	{
		if (!ft_check_space(str, index))
			size++;
		index++;
	}
	result = (char *)malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	result[size] = '\0';
	while (index >= 0)
	{
		if (!ft_check_space(str, index))
		{
			result[size] = str[index];
			size--;
		}
		index--;
	}
	free(str);
	return (result);
}