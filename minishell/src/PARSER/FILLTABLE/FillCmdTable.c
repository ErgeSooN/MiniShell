/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FillCmdTable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:32:23 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:32:23 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	fill_cmdtable -> fill_cmdnode ile düğümlere komut öğelerini ekler.
*/

void	fill_cmdtable(void)
{
	t_cmdlist	*temp_cmdtable;
	t_lexlist	*temp_lexlist;

	if (!g_core.cmd_table)
		return ;
	temp_cmdtable = g_core.cmd_table;
	temp_lexlist = g_core.lex_table;
	while (temp_cmdtable)
	{
		fill_cmdnode(temp_cmdtable, &temp_lexlist);
		if (temp_lexlist && *temp_lexlist->content == *PIPE)
			temp_lexlist = temp_lexlist->next;
		temp_cmdtable = temp_cmdtable->next;
	}
}

/*
	fill_cmdnode -> komut düğümünün yolunu (path) oluşturmak için kullanılır.
	Bunu create_path işlevini kullanarak yapar.
*/

void	fill_cmdnode(t_cmdlist *node, t_lexlist **lex_list)
{
	char	**path_holder;
	int		is_begin;

	node->path = create_path(*lex_list);
	path_holder = node->path;
	is_begin = 0;
	while (*lex_list && (*lex_list)->type != SIGN_PIPE)
	{
		if (create_new_filelist(node, lex_list))
			continue ;
		if (!(is_begin++) && (*lex_list)->content)
			expand_cmd(&((*lex_list)->content));
		if ((*lex_list)->content)
			*(path_holder++) = (*lex_list)->content;
		*lex_list = (*lex_list)->next;
	}
	if (node->path)
		node->cmd = node->path[0];
}
