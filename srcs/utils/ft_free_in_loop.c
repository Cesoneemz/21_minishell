/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_in_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wmiyu <wmiyu@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 15:51:03 by wlanette          #+#    #+#             */
/*   Updated: 2022/10/25 19:23:57 by wmiyu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exit(t_tokens **tokens, t_info **info, char *str)
{
	//rl_clear_history();
	ft_free_env(&(*info)->env);
	free(*info);
	free(*tokens);
	free(str);
}

void	ft_free_all(t_tokens **tokens, char *str)
{
	ft_free_tokens(tokens);
	free(str);
}
