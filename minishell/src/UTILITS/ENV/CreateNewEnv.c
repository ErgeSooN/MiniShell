/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateNewEnv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:33:30 by ayaman            #+#    #+#             */
/*   Updated: 2023/04/07 21:57:24 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*Main fonksiyonundaki 3. parametreyi bağlı listeye yerleştirir(doldurur).*/
void	fill_envs(char **env)
{
	while (env && *env)
		add_newenv(&g_core.env_table, *(env++));
}

/*
	Eğer bağlı liste yoksa kendisi oluşturur ve ilkk başta çevresel değikeni alır. 
	Daha sonra '=' den sonrasında karakter var mı kontrol edilir eğer varsa ft_strdup ile
	son düğümğn contentine kopyalanır.
*/
t_env	*add_newenv(t_env **env_table, char *env)
{
	t_env	*last_node;
	char	*content;

	if (!*env_table)
	{
		*env_table = (t_env *)malloc(sizeof(t_env));
		last_node = *env_table;
	}
	else
	{
		last_node = *env_table;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = (t_env *)malloc(sizeof(t_env));
		last_node = last_node->next;
	}
	last_node->env_name = get_env_name(env);
	content = env + ft_strlen(last_node->env_name);
	if (*content == '=' && *(content + 1))
		last_node->content = ft_strdup(content + 1);
	else
		last_node->content = NULL;
	last_node->next = NULL;
	return (last_node);
}
