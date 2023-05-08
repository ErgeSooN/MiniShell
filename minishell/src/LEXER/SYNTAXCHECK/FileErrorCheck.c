/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FileErrorCheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:31:15 by ayaman            #+#    #+#             */
/*   Updated: 2023/05/03 11:03:39 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Komut satırına girilen karakter <<, <, >>, > bunlardan biri ise bu fonksiyona gelir.
  Eğer metakarakter sonrası bir text yok ise else sorgusuna girer. Eğer farklı bir karakter var ise
  if sorgusuna girer ve iki sorguda da 258 hata kodunu döndürür.
  free_lexer_without_heradoc fonksiyonuna yönlendirme yapar.
  Bu fonksiyon bizim bizim terminalde girdiğimiz karakterleri kontrol etmemizi sağlar.
*/

int	file_error_check(t_lexlist *lex_list)
{
	if (!lex_list->next || (lex_list->next && lex_list->next->type != TEXT))
	{
		if (lex_list->next)
		{
			print_error("-bash: syntax error near unexpected token '",
				lex_list->next->content, "'\n");
			g_core.exec_output = 258 ;
			free_lexer_without_heradoc(lex_list);
			return (0);
		}
		else
		{
			print_error("-bash: syntax error near unexpected token '",
				"newline", "'\n");
			g_core.exec_output = 258 ;
			free_lexer_without_heradoc(lex_list);
			return (0);
		}
	}
	return (1);
}
