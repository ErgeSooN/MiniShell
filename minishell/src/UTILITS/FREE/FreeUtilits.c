/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FreeUtilits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:34:05 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:34:05 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	metakarakterlerin dinamik olarak tahsis edilmiş bellek alanını serbest bırakır.
*/

void	free_metachars(void)
{
	char	**temp_metachars;

	temp_metachars = g_core.metachars;
	if (!temp_metachars)
		return ;
	while (temp_metachars && *temp_metachars)
		free(*(temp_metachars++));
	free(g_core.metachars);
}

/*
	shell ortam tablosundaki tüm değişkenlerin isim ve değerlerini içeren yapıları
	hafızadan siler ve temizler.
*/

void	free_envtable(void)
{
	t_env	*env;
	t_env	*temp_env;

	env = g_core.env_table;
	while (env)
	{
		temp_env = env;
		env = env->next;
		free(temp_env->env_name);
		free(temp_env->content);
		free(temp_env);
	}
}
