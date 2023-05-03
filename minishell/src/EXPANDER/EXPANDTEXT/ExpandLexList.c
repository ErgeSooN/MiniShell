/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandLexList.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbolat <bbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:29:51 by bbolat            #+#    #+#             */
/*   Updated: 2023/01/19 13:29:51 by bbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	expand_text -> Her karakteri tarar. her karakterin tipine göre 
	farklı işlemler yapar. Tek tırnak ya da çift tırnak
	işaretiyle çevrelenmiş metinleri ve $ veya ~ karakterleriyle başlayan
	metinleri tespit eder.
	Bu metinler daha sonra ilgili genişletme işlevine gönderilir
	sonuç, ilgili karakter yerine yerleştirilir.
*/

void	expand_values_from_lexlist(void)
{
	t_lexlist	*lex_table;

	lex_table = g_core.lex_table;
	while (lex_table)
	{
		if (lex_table->type == TEXT)
			expand_text(lex_table, 0);
		else if (lex_table->next && lex_table->type != SIGN_PIPE)
		{
			if (lex_table->type != SIGN_DOUBLE_LESS)
				expand_text(lex_table->next, 1);
			lex_table = lex_table->next;
		}
		lex_table = lex_table->next;
	}
}

void	expand_text(t_lexlist *lex_table, int is_after_meta)
{
	char	*cmd;
	int		flag;
	char	*ptr;

	cmd = lex_table->content;
	ptr = NULL;
	flag = 0;
	while (*cmd)
	{
		if (*cmd == '\'' && (!flag || flag == 1))
			flag = flag ^ 1;
		else if (*cmd == '\"' && (!flag || flag == 2))
			flag = flag ^ 2;
		else if ((!flag || flag == 2) && (*cmd == *DOLLAR || *cmd == *TILDA))
			expand_order(&ptr, &cmd);
		else
			str_addchar(&ptr, *cmd);
		cmd++;
	}
	if (is_after_meta && !ptr)
		return ;
	free(lex_table->content);
	lex_table->content = ptr;
}
