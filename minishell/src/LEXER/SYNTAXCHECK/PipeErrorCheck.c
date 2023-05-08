/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PipeErrorCheck.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:31:23 by ayaman            #+#    #+#             */
/*   Updated: 2023/05/03 21:46:40 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Eğer pipe karakteri iki defa kullanılmışsa ilk if sorgusuna girip hata mesajı döndürür.
  Eğer bir defa kullanılmışsa run_miss_arguman fonksiyonuna gidilir. 
*/

int	pipe_error_check(t_lexlist *lex_list)
{
	if (lex_list->next && lex_list->next->type == SIGN_PIPE)
		return (print_lex_error(lex_list));
	else if (!lex_list->next)
		return (run_miss_arg(lex_list));
	return (1);
}

/* 
  Bu fonksiyon eksik girilen argümanı ilk başta ptr değişkenine alır. Daha sonra
  lex_list'e ekleme yapıp classify fonksiyonu ile sınıflandırır. str_addchar ve own_strjoin
  fonksiyonları ile de g_core.cmd değişkenine ekleme yapar.
*/

int	run_miss_arg(t_lexlist *lex_list)
{
	char	*ptr;

	ptr = get_missing_arg();
	if (!ptr)
		return (1);
	create_lexlist(ptr, &lex_list);
	classify(lex_list);
	str_addchar(&g_core.cmd, ' ');
	own_strjoin(&g_core.cmd, ptr);
	free(ptr);
	if (str_compare(lex_list->next->content, PIPE))
		return (-1);
	return (1);
}
