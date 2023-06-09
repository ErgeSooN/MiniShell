/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UpdateEnv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:33:48 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:33:48 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Bu fonksiyon bizim çevresel değişkenleri güncellememiz
  için gerekli olan bir fonksiyondur. Eğer eşleşen bir 
  çevresel değişken görülürse ilk başta içerisi freelenir daha 
  sonra yeni env strjoin fonksiyonu ile içerisine doldurulur.
*/

int	update_env(char *env_name, char *new_arg)
{
	t_env	*env;

	env = g_core.env_table;
	while (env)
	{
		if (str_compare(env->env_name, env_name))
		{
			if (env->content)
				free(env->content);
			env->content = NULL;
			if (!new_arg)
				return (1);
			own_strjoin(&env->content, new_arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
