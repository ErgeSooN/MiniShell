/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreatePath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:32:19 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:32:19 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	create_path -> Bir t_lexlist listesinin type'ı TEXT olan öğelerinin sayısını
	hesaplar ve bu sayı kadar boyutlu bir char tipi çift işaretçisi (char **) oluşturur.
	Bu işaretçi, komutun yolunu (path) ve argümanlarını tutmak için kullanılacak.
*/

char	**create_path(t_lexlist *lex_list)
{
	int		count;
	char	**path;

	count = 0;
	while (lex_list && lex_list->type != SIGN_PIPE)
	{
		if (lex_list->type == TEXT && lex_list->content)
			count++;
		else
		{
			lex_list = lex_list->next;
			if (lex_list)
				lex_list = lex_list->next;
			continue ;
		}
		lex_list = lex_list->next;
	}
	if (!count)
		return (NULL);
	path = (char **)malloc(sizeof(char *) * (count + 1));
	path[count] = NULL;
	return (path);
}
