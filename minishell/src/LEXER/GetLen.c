/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetLen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:31 by ayaman            #+#    #+#             */
/*   Updated: 2023/05/01 10:25:49 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
  bu fonksiyon girilen metindeki ilk karakter ile diğer karakterleri 
  karşılaştırıyor eğer bir eşitlik var ise o uzunluğu döndürüyor. Örnek
  olarak "ali eren"asd metnini kullanabiliriz. Buradaki uzunluk değeri 9'dur.
*/

size_t	get_quotelen(char *cmd_line)
{
	char	c;
	size_t	count;

	c = *cmd_line;
	count = 1;
	while (*(++cmd_line))
	{
		count++;
		if (*cmd_line == c)
			break ;
	}
	return (count);
}

/*
  Bu fonksiyon terminale girilen komut satırının uzunluğunu alır.
  bu kodu yapma sebeplerimiz arasında malloc ile yer açmak için uzunluğu bulmak.
*/

size_t	get_cmdlen(char *cmd_line)
{
	size_t	count;
	size_t	quotelen;
	char	*is_meta;

	count = 0;
	while (cmd_line && *cmd_line && *cmd_line != ' ')
	{
		is_meta = compare_metachars(cmd_line);
		if (is_meta)
		{
			if (!count)
				count += ft_strlen(is_meta);
			break ;
		}
		if ((*cmd_line == *SINGLE_QUOTE || *cmd_line == *DOUBLE_QUOTE))
		{
			quotelen = get_quotelen(cmd_line);
			count += quotelen;
			cmd_line += quotelen;
			continue ;
		}
		count++;
		cmd_line++;
	}
	return (count);
}
