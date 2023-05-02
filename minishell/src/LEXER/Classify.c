/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:11 by bbolat            #+#    #+#             */
/*   Updated: 2023/05/02 11:25:55 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
                                        ## (*METACHARS - 1) ##
  Metachars - 1 demenin sebebi, '>>' ve '<<' metakarakterlerde ascii kodu tek '<' '>' 2 ile çarpıldığı için 
  '|' karakteri ile çakışma oluyor ama biz bunu istemediğimiz için hepsini 1 eksiltiyoruz ve bu sefer çakışma
  ortadan kalkıyor.
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
