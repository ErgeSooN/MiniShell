/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CompareMetachars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:34:12 by ayaman            #+#    #+#             */
/*   Updated: 2023/04/28 20:17:40 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Metakarakterlerin karşılaştırmasını yapar. Karşılaştırmayı da bizim önceden 
  tanımladığımız metakarakterler ile karşılaştırır eğer bir eşleşme var ise 
  eşleşmeyi dööndürür eğer eşleşme yok ise NULL döndürür.
*/

char	*compare_metachars(char *cmd_line)
{
	char	**meta_chars;

	if (!cmd_line)
		return (NULL);
	meta_chars = g_core.metachars;
	while (meta_chars && *meta_chars)
	{
		if ((*cmd_line == **meta_chars && !*(*meta_chars + 1))
			|| (*cmd_line == **meta_chars
				&& *(*meta_chars + 1) == *(cmd_line + 1)))
			return (*meta_chars);
		meta_chars++;
	}
	return (NULL);
}
