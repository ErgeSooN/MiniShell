/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FreeLexer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:38 by bbolat            #+#    #+#             */
/*   Updated: 2023/05/03 11:59:27 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

int	skip_heradoc(t_lexlist **lex, t_lexlist **temp, t_lexlist *stop, int *flag)
{
	if (stop == *lex)
		*flag = 1;
	if ((*lex)->type == SIGN_DOUBLE_LESS && !*flag)
	{
		if ((*lex) && (*lex) != stop)
			*lex = (*lex)->next;
		*temp = *lex;
		*lex = (*lex)->next;
		return (1);
	}
	return (0);
}

/*
  Eğer file_error_check fonksiyonunda if döngünün içerisine girilirse bu 
  fonksiyona gelinir 
*/

void	free_lexer_without_heradoc(t_lexlist *stop_list)
{
	t_lexlist	*lexer;
	t_lexlist	*temp_lexer;
	int			flag;

	lexer = g_core.lex_table;
	flag = 0;
	while (lexer)
	{
		if (skip_heradoc(&lexer, &temp_lexer, stop_list, &flag))
			continue ;
		if (g_core.lex_table == lexer)
		{
			g_core.lex_table = g_core.lex_table->next;
			temp_lexer = g_core.lex_table;
		}
		else
			temp_lexer->next = lexer->next;
		free(lexer->content);
		free(lexer);
		if (g_core.lex_table == temp_lexer)
			lexer = temp_lexer;
		else
			lexer = temp_lexer->next;
	}
}

void	free_lexer(void)
{
	t_lexlist	*lexer;
	t_lexlist	*temp_lexer;

	lexer = g_core.lex_table;
	while (lexer)
	{
		temp_lexer = lexer;
		lexer = lexer->next;
		if (temp_lexer->content)
			free(temp_lexer->content);
		free(temp_lexer);
	}
	g_core.lex_table = NULL;
}
