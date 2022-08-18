#include "minishell.h"

static void	ft_get_type_of_token(t_tokens *tokens)
{
	if (ft_strncmp(tokens->value, ">", 1) == 0)
		tokens->type = TRUNC;
	if (ft_strncmp(tokens->value, "<", 1) == 0)
		tokens->type = INPUT;
	if (ft_strncmp(tokens->value, ">>", 2) == 0)
		tokens->type = APPEND;
	if (ft_strncmp(tokens->value, "<<", 2) == 0)
		tokens->type = HEREDOC;
	if (ft_strncmp(tokens->value, "|", 1) == 0)
		tokens->type = PIPE;
	if (tokens->type == 0)
		tokens->type = WORD;
}

static int	ft_tokenize_quotes(char *str, int index, t_tokens *tokens)
{
	int	temp;

	temp = index;
	while (str[index] != '\"' && str[index] != '\'')
	{
		tokens->len++;
		index++;
	}
	tokens->value = ft_substr(str, temp, tokens->len);
	if (str[index] == '\"')
		tokens->type = EXP_FIELD;
	else
		tokens->type = FIELD;
	return (tokens->len + 2);
}

static int	ft_tokenize_str(char *str, int index, t_tokens *tokens)
{
	int	temp;

	temp = index;
	if (str[index] == '<' || str[index] == '>')
	{
		index++;
		if (str[index] == '<' || str[index] == '>')
		{
			tokens->value = ft_substr(str, temp, 2);
			return (2);
		}
		tokens->value = ft_substr(str, temp, 1);
		return (1);
	}
	if (str[index] == '|')
	{
		tokens->value = ft_substr(str, temp, 1);
		return (1);
	}
	tokens->len = ft_get_len_of_token(str, index, tokens);
	tokens->value = ft_substr(str, temp, tokens->len);
	return (tokens->len);
}

static int	ft_tokenize_sep(char *str, int index, t_tokens *tokens)
{
	int	temp;

	temp = index;
	while (str[index] == ' ')
	{
		tokens->len++;
		index++;
	}
	tokens->value = ft_substr(str, temp, tokens->len);
	tokens->type = SEP;
	return (tokens->len);
}

void	ft_lexer(char *str, t_tokens *tokens)
{
	int			index;

	if (!ft_check_quotes(str))
		return ;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index + 1] != '\0' && index != 0)
		{
			tokens->next = ft_new_token();
			tokens = tokens->next;
		}
		if (str[index] == ' ')
		{
			index += ft_tokenize_sep(str, index, tokens);
			continue ;
		}
		if (str[index] == '\"' || str[index] == '\'')
		{
			index += ft_tokenize_quotes(str, index + 1, tokens);
			continue ;
		}
		index += ft_tokenize_str(str, index, tokens);
		ft_get_type_of_token(tokens);
	}
}
