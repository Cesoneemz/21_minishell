/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_additional.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 09:18:34 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/26 09:29:43 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_redirect(t_tokens *temp)
{
	int		redirect_count;
	char	**redirect;

	redirect_count = ft_get_redirection_count(temp);
	redirect = NULL;
	if (redirect_count > 0)
	{
		redirect = malloc(sizeof(char *) * (redirect_count + 1));
		if (!redirect)
			return (NULL);
		redirect[redirect_count] = NULL;
	}
	return (redirect);
}

static int	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
	{
		return (1);
	}
	return (0);
}

char	*ft_parse_cmd_part3(t_token_types type, char *cmd, int *index)
{
	char	*temp;
	char	*expanded;

	temp = NULL;
	expanded = ft_calloc(1, sizeof(char));
	if ((cmd[*index] == '\'' || cmd[*index] == '\"') && type == WORD)
	{
		temp = expanded;
		expanded = ft_strjoin(expanded, \
		ft_word_treatment(cmd, index, cmd[*index]));
		free(temp);
	}
	if (ft_isascii(cmd[*index]) && !ft_is_quote(cmd[*index]))
		expanded = ft_add_char_to_str(expanded, cmd[*index]);
	(*index)++;
	if (ft_strlen(expanded) <= 0)
		expanded = ft_strjoin(expanded, cmd);
	return (expanded);
}
