/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandText.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbolat <bbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:29:56 by bbolat            #+#    #+#             */
/*   Updated: 2023/01/19 13:29:56 by bbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	string içinde geçen $ veya ~ karakterlerinin uygun şekilde 
	genişletilmesini sağlar.
	

	$ -> expand_dollar fonksiyonu çağırılır. 
	$ karakterinden sonra gelen stringi okur ve bu stringin bir 
	çevresel değişkenin adı olduğunu varsayar. Bu değişkenin değerini
	g_core.env_table listesinden okuyarak genişletilmiş stringe ekler.

	~ -> expand_envs fonksiyonu çağırılır. 
	1.parametre olarak aldığı char pointer'ı genişletilmiş bir string 
	olarak doldurur. 2.parametre olara bu genişletmenin yapılacağı string 
	verilir ("HOME"). g_core.env_table listesinde bu isimle bir 
	çevresel değişken arar ve değerini genişletilmiş stringe ekler.
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

void	expand_order(char **dst, char **src)
{
	if (**src == *DOLLAR)
		expand_dollar(dst, src);
	else
		expand_envs(dst, "HOME");
}
