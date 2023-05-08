/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AddLexNode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:16 by ayaman            #+#    #+#             */
/*   Updated: 2023/04/27 22:18:12 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
  Bu kod eğer cmd_table değişkeni yoksa oluşturur daha sonra bağlı listenin sonuna yeni 
  yeni bir düğüm ekler bunu yapmamızın amacı kullanıcı bir komut satırına yeni bir argüman 
  eklediğinde veya yeni bir dosya yolunu belirttiğinde, bu fonksiyonun kullanılabilmesidir.
*/

t_lexlist	*add_new_lex_node(t_lexlist **cmd_table)
{
	t_lexlist	*new_node;

	if (!*cmd_table)
	{
		new_node = (t_lexlist *)malloc(sizeof(t_lexlist));
		new_node->content = NULL;
		new_node->type = 0;
		new_node->next = NULL;
		*cmd_table = new_node;
		return (*cmd_table);
	}
	new_node = *cmd_table;
	while (new_node->next)
		new_node = new_node->next;
	new_node->next = (t_lexlist *)malloc(sizeof(t_lexlist));
	new_node->next->content = NULL;
	new_node->next->type = 0;
	new_node->next->next = NULL;
	return (new_node->next);
}
