/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:11 by bbolat            #+#    #+#             */
/*   Updated: 2023/05/01 15:16:09 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
							## (*METACHARS - 1) ##
  Metachars - 1 demenin sebebi, metachars dizisinin ilk karakterinin ‘\0’ olması 
  ve bu karakterin tipini belirlemek istemediğimiz için olabilir. 
  Bu şekilde, metachars dizisindeki diğer karakterlerin tipleri 0’dan başlayarak sıralanır.  
  Eğer metachars - 1 demeseydik, lex_table->type alanına ‘\0’ karakterinin tipini atamış olurduk. 
  Bu da istemediğimiz bir durum olurdu.
*/

/*
  Bu kod, girdi olarak verilen bir metni sözdizimsel olarak analiz edip her sözcüğün tipini belirler.
  Bu şekilde, program hangi sözcüğün bir yerleşik fonksiyon olduğunu 
  veya hangi sözcüğün bir boru veya yönlendirme operatörü olduğunu anlayabilir. 
*/

void	classify(t_lexlist *lex_table)
{
	char	*metachars;

	if (!lex_table)
		return ;
	while (lex_table)
	{
		metachars = compare_metachars(lex_table->content);
		if (metachars)
			lex_table->type = (*metachars - 1) * ft_strlen(metachars);
		else
			lex_table->type = 0;
		lex_table = lex_table->next;
	}
}
