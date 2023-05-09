/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandCmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:28:51 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:28:51 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
	expand_cmd ->  verilen bir komut satırı argümanının PATH çevresel değişkenindeki 
	değerlerle genişletilmesini sağlar.
*/

void	expand_cmd(char **dst)
{
	t_env	*temp_env;

	temp_env = g_core.env_table;
	while (temp_env && *dst && **dst)
	{
		if (str_compare("PATH", temp_env->env_name))
		{
			expand_from_env_value(dst, temp_env->content);
			return ;
		}
		temp_env = temp_env->next;
	}
}

/*
	expand_from_env_value -> Komut yürütüldüğünde kullanılan PATH değişkeninin değerini genişletmek 
	için kullanılır. her yolun sonunda ':' karakteriyle bittiği varsayımına dayanarak çalışır.
	yani -> /usr/bin:/bin:/usr/sbin:/sbin bu gibi PATH'i gezer.

	access -> kullanıcının dosyayı okuyabilme yetkisine sahip olup olmadığını kontrol eder. 
	işlem yapılabiliyorsa 0, yapılamıyorsa -1 döner ve errno değişkeni ayarlanır.
	F_OK -> existence(varoluş)
*/

void	expand_from_env_value(char **dst, char *content)
{
	char	*control_ptr;

	while (content && *content)
	{
		control_ptr = get_arg_from_env_value(&content, *dst);
		if (!access(control_ptr, F_OK))
		{
			free(*dst);
			*dst = control_ptr;
			return ;
		}
		free(control_ptr);
	}
}

/*
	get_arg_from_env_value -> , PATH değişkeninin bir parçasını ve genişletilecek bir argüman adını alır. 
	':' karakterine kadar olan tüm karakterleri ptr'ye kopyalar. Sonra ptr'ye "/" karakteri eklenir.
*/

char	*get_arg_from_env_value(char **envs, char *search_arg_name)
{
	char	*ptr;
	int		count;
	char	*temp_envs;

	count = 0;
	temp_envs = *envs;
	while (*temp_envs && *temp_envs != ':')
	{
		count++;
		temp_envs++;
		(*envs)++;
	}
	if (!count)
		return (NULL);
	if (**envs)
		(*envs)++;
	ptr = (char *)malloc(sizeof(char) * (count + 1));
	ptr[count] = 0;
	while (--count > -1)
		ptr[count] = *(--temp_envs);
	str_addchar(&ptr, '/');
	own_strjoin(&ptr, search_arg_name);
	return (ptr);
}
