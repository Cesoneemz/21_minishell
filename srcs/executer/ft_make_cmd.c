/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 21:32:00 by wmiyu             #+#    #+#             */
/*   Updated: 2022/09/27 21:33:21 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_cmd_list(t_info *info)
{
	int		i;
	int		j;
	int		len;
	int		summ;
	t_cmd	*tmp_cmd;

	i = 0;
	len = 0;
	summ = 0;
	while (i < info->cmd_count)
	{
		summ = ft_strlen(info->cmd_list[i].cmd);
		printf(" --- t_cmd# %d : [%s] ---\n", i, info->cmd_list[i].cmd);
		tmp_cmd = &info->cmd_list[i];
		j = 0;
		while (tmp_cmd->args[j])
		{
			summ += ft_strlen(tmp_cmd->args[j]);
			printf(" args# %d : %s\n", j, tmp_cmd->args[j]);
			j++;
		}
		i++;
		printf("__summ: %d\n", summ);
	}
	return (summ);
}

char **make_cmd_list(t_info *info)
{
	int		i;
	int		j;
	t_cmd	*tmp_cmd;
	char	**cmd_list;
	char	*tmp;

	i = 0;
	cmd_list = (char **)malloc(sizeof(char *) * (info->cmd_count + 1));
	tmp = NULL;
	while (i < info->cmd_count)
	{
		cmd_list[i] = ft_strjoin(info->cmd_list[i].cmd, "");
		tmp_cmd = &info->cmd_list[i];
		j = 0;
		while (tmp_cmd->args[j])
		{
			tmp = cmd_list[i];
			cmd_list[i] = \
			ft_strjoin(ft_strjoin(cmd_list[i], " "), tmp_cmd->args[j]);
			free (tmp);
			j++;
		}
		i++;
	}
	cmd_list[i] = NULL;
	return (cmd_list);
}
