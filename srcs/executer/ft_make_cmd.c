/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:32:00 by wmiyu             #+#    #+#             */
/*   Updated: 2022/09/28 23:02:19 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tmp_tokens(t_info *info)
{
	int			i;
	t_tokens	*tmp_tokens;

	i = 0;
	while (i < info->cmd_count)
	{
		tmp_tokens = info->cmd_list[i].sep_tokens;
		printf("-=-=-=-=-=-=-=-=s\n");
		while (tmp_tokens)
		{
			printf("%s\n", tmp_tokens->value);
			tmp_tokens = tmp_tokens->next;
		}
		printf("-=-=-=-=-=-=-=-=s\n");
		i++;
	}
}

char	**make_cmd_list(t_info *info)
{
	int			i;
	t_tokens	*tmp_tokens;
	char		**cmd_list;
	char		*tmp;

	cmd_list = (char **)malloc(sizeof(char *) * (info->cmd_count + 1));
	cmd_list[info->cmd_count] = NULL;
	i = 0;
	tmp = NULL;
	while (i < info->cmd_count)
	{
		tmp_tokens = info->cmd_list[i].sep_tokens;
		while (tmp_tokens)
		{
			if (!cmd_list[i])
				cmd_list[i] = ft_strjoin(tmp_tokens->value, "");
			else
			{
				tmp = cmd_list[i];
				cmd_list[i] =  \
				ft_strjoin(ft_strjoin(cmd_list[i], " "), tmp_tokens->value);
				free (tmp);
			}
			tmp_tokens = tmp_tokens->next;
		}
		i++;
	}
	return (cmd_list);
}
