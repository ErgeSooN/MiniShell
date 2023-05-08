/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:01 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:30:01 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
	expander => parser tarafından belirlenen parametreleri genişletir ve komutu
	çalıştırmak için gereken bilgileri toplar.
	örneğin "~/tmp" -> "/home/kullanıcıadı/tmp"
			"ls *" -> ls'i tüm dosya ve klasörlerle çalışacak şekilde genişletir.
*/

void	expander(void)
{
	if (g_core.exec_output == 2)
		return ;
	expand_values_from_lexlist();
	clear_void_contents();
}
