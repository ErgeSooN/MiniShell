/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandText.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:29:56 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:29:56 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	g_core.env_table çeşitli ortam değişkenlerini ve bunların 
	değerlerini içerir. while ile t_env yapısındaki tüm öğeleri kontrol eder 
	ve ptr değişkeni ile karşılaştırır. Eğer ptr, t_env yapısındaki bir ortam 
	değişkeni adı ile eşleşirse, genişletilmiş metni oluşturmak için t_env 
	yapısındaki değeri kullanır.
*/

void	expand_envs(char **dst, char *ptr)
{
	t_env	*copy_envs;

	copy_envs = g_core.env_table;
	while (copy_envs)
	{
		if (str_compare(ptr, copy_envs->env_name))
		{
			own_strjoin(dst, copy_envs->content);
			break ;
		}
		copy_envs = copy_envs->next;
	}
}

/*
	string içinde geçen $ veya ~ karakterlerinin uygun şekilde 
	genişletilmesini sağlar.
	

	$ -> expand_dollar fonksiyonu çağırılır. 
	$ karakterinden sonra gelen stringi okur ve bu stringin bir 
	çevresel değişkenin adı olduğunu varsayar. Bu değişkenin değerini
	g_core.env_table listesinden okuyarak genişletilmiş stringe ekler.

	~ -> expand_envs fonksiyonu çağırılır. 
	HOME ortam değişkeninin değerini alır ve bu değeri genişletilmiş metnin 
	sonucu olarak kullanır. g_core.env_table listesinde bu isimle bir 
	çevresel değişken arar ve değerini genişletilmiş stringe ekler.
*/

void	expand_order(char **dst, char **src)
{
	if (**src == *DOLLAR)
		expand_dollar(dst, src);
	else
		expand_envs(dst, "HOME");
}
