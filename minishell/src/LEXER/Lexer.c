/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbolat <bbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:59 by bbolat            #+#    #+#             */
/*   Updated: 2023/01/27 19:56:21 by bbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
	<a.txt cat| ls| wc -l | echo "ahmet $HOME''"selam
	<, a.txt, cat, |, ls, |, wc, -l, |, echo,
	"ahmet $HOME''"selam'$PATH'ec

	This section purpose is seperate the commands to linked list.
	function seperates each command also flags to linked list.
*/
void	lexer(void)
{
	g_core.lex_table = NULL;
	create_lexlist(g_core.cmd, &(g_core.lex_table));
	classify(g_core.lex_table);
	syntax_check();
}
