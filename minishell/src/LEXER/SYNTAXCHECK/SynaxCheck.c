/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SynaxCheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:31:27 by ayaman            #+#    #+#             */
/*   Updated: 2023/05/02 12:26:05 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  lex_list olduğu sürece bu fonksiyona girilir. ve tüm nodeleri geze geze 
  hata var mı yok mu genel kontrolü burada başlar.
*/

void	syntax_check(void)
{
	t_lexlist	*lex_list;
	int			syntax_error;

	lex_list = g_core.lex_table;
	while (lex_list)
	{
		syntax_error = syntax_error_check(lex_list);
		if (syntax_error == -1)
			break ;
		else if (!syntax_error)
			continue ;
		if (g_core.lex_table)
			lex_list = lex_list->next;
		else
			lex_list = NULL;
	}
}

/*
  Bu fonksiyon 3 farklı error kontrolü yapar. İlk sorguya birden fazla pipe karakteri
  varsa girilir ve hata çıktısı sağlanır. İkinci sorguda dosyanın açılabilmesi için
  gerekli bilgiler var mı yok mu kontrolü yapılır. Üçüncü sorguda ise pipe(boru yolu)
  hatası var mı yok mu onun kontrolünü yapar.
*/

int	syntax_error_check(t_lexlist *lex_list)
{
	int	pipe_error;

	if (lex_list == g_core.lex_table && lex_list->type == SIGN_PIPE)
	{
		print_lex_error(lex_list);
		return (-1);
	}
	else if (lex_list->type != TEXT && lex_list->type != SIGN_PIPE)
	{
		if (!file_error_check(lex_list))
			return (-1);
	}
	else if (lex_list->type == SIGN_PIPE)
	{
		pipe_error = pipe_error_check(lex_list);
		if (pipe_error < 0)
			return (0);
		else if (!pipe_error)
			return (-1);
	}
	return (1);
}
