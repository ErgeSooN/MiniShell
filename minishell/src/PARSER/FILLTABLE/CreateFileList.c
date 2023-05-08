/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateFileList.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:32:14 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:32:14 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	create_new_filelist -> t_cmdlist yapısındaki bir düğüm ve t_lexlist yapısındaki
	bir işaretçi alır. Düğüm yürütülecek olan komutu ve ilgili dosya listesini içerir.
	İşaretçi komut dizisindeki metinleri ve özel karakterleri içeren bir liste işaretçisidir.

	(*lex_list)->next işaretçisi kullanılarak dosya adı içeriği elde edilir ve filename 
	değişkenine atanır. Ancak, (*lex_list)->next NULL işaretçisi ise, dosya adı atanmaz.

	add_filelist -> Dosya listesine yeni bir dosya eklenir. Bu yeni dosyanın dosya adı,
	filename değişkeninden ve özel karakter, (*lex_list)->content işaretçisi içeriğinden elde edilir. 

	temp_filelist->> işaret edilen dosyanın özellikleri ayarlar.
*/

int	create_new_filelist(t_cmdlist *node, t_lexlist **lex_list)
{
	char		*meta;
	char		*filename;
	t_filelist	*temp_filelist;

	if (((*lex_list)->type) == TEXT)
		return (0);
	meta = compare_metachars((*lex_list)->content);
	filename = NULL;
	if ((*lex_list)->next)
		filename = (*lex_list)->next->content;
	if (*meta != *PIPE)
	{
		temp_filelist = add_filelist(&(node->files), filename, meta);
		temp_filelist->metachar = (*lex_list)->content;
	}
	(*lex_list) = (*lex_list)->next;
	if (*lex_list)
		(*lex_list) = (*lex_list)->next;
	return (1);
}

t_filelist	*add_filelist(t_filelist **file_list, char *filename, char *meta)
{
	t_filelist	*temp_filelist;

	if (!*file_list)
	{
		*file_list = (t_filelist *)malloc(sizeof(t_filelist));
		temp_filelist = *file_list;
	}
	else
	{
		temp_filelist = *file_list;
		while (temp_filelist->next)
			temp_filelist = temp_filelist->next;
		temp_filelist->next = (t_filelist *)malloc(sizeof(t_filelist));
		temp_filelist = temp_filelist->next;
	}
	temp_filelist->fd = 0;
	temp_filelist->filename = filename;
	temp_filelist->metachar = meta;
	temp_filelist->next = NULL;
	return (temp_filelist);
}
