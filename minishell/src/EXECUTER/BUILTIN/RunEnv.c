/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunEnv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:32 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:32 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	tüm environment variable'ları yazdırmakla sorumludur. Fonksiyon, cmd_node 
	parametresi olarak bir komut düğümü alır ve cmd_node->outfile üzerindeki 
	çıktıya environment variable'larını yazdırır.
*/

void	run_env(t_cmdlist *cmd_node)
{
	t_env	*temp_env;

	temp_env = g_core.env_table;
	while (temp_env)
	{
		if (temp_env->content)
		{
			write(cmd_node->outfile, temp_env->env_name,
				ft_strlen(temp_env->env_name));
			write(cmd_node->outfile, "=", 1);
			write(cmd_node->outfile, temp_env->content,
				ft_strlen(temp_env->content));
			write(cmd_node->outfile, "\n", 1);
		}
		temp_env = temp_env->next;
		g_core.exec_output = 0;
	}
}
