/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:32:00 by wmiyu             #+#    #+#             */
/*   Updated: 2022/10/25 00:49:24 by wlanette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**make_cmd_list(t_info *info)
{
	int			i;
	t_tokens	*tmp_tokens;
	char		**cmd_list;

	cmd_list = ft_calloc(info->cmd_count + 1, sizeof(char *));
	i = 0;
	while (i < info->cmd_count)
	{
		tmp_tokens = info->cmd_list[i].sep_tokens;
		while (tmp_tokens)
		{
			if (!cmd_list[i])
				cmd_list[i] = ft_strjoin(tmp_tokens->value, "");
			else
			{
				cmd_list[i] = \
				ft_strjoin(ft_strjoin(cmd_list[i], "\t"), tmp_tokens->value);
			}
			tmp_tokens = tmp_tokens->next;
		}
		i++;
	}
	return (cmd_list);
}

int	count_tmp_tokens2(t_info *info)
{
	int			i;
	int			count;
	t_tokens	*tmp_tokens;

	i = 0;
	count = -1;
	while (i < info->cmd_count)
	{
		count++;
		tmp_tokens = info->cmd_list[i].sep_tokens;
		while (tmp_tokens)
		{
			tmp_tokens = tmp_tokens->next;
			count++;
		}
		i++;
	}
	return (count);
}

char	**make_cmd_list2(t_info *info)
{
	int			i;
	t_tokens	*tmp_tokens;
	char		**cmd_argv;
	int			count;

	count = count_tmp_tokens2(info);
	cmd_argv = ft_calloc(count + 2, sizeof(char *));
	cmd_argv[0] = ft_strjoin("-=-=-=-=-=", "");
	cmd_argv[count + 1] = NULL;
	i = 0;
	count = 0;
	while (i < info->cmd_count)
	{
		tmp_tokens = info->cmd_list[i].sep_tokens;
		count++;
		while (tmp_tokens)
		{
			cmd_argv[count] = ft_strjoin(tmp_tokens->value, "");
			tmp_tokens = tmp_tokens->next;
			count++;
		}
		if (++i < info->cmd_count)
			cmd_argv[count] = ft_strjoin("|", "");
	}
	return (cmd_argv);
}
/*void	print_tmp_tokens(t_info *info)
{
	int			i;
	t_tokens	*tmp_tokens;

	i = 0;
	printf("-=-=-=-=-=-=-=-=s\n");
	while (i < info->cmd_count)
	{
		tmp_tokens = info->cmd_list[i].sep_tokens;
		while (tmp_tokens)
		{
			printf("[:%u] %s \t \n", tmp_tokens->type, tmp_tokens->value);
			tmp_tokens = tmp_tokens->next;
		}
		i++;
		if (i < info->cmd_count)
			printf("-=-=-=-= | -=-=-=-=s\n");
	}
}
*/