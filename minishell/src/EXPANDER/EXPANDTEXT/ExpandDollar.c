/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExpandDollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:29:09 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:29:09 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	expand_dollar -> $ karakteriyle başlayan bir metnin, hangi değişkeni temsil 
	ettiğine bağlı olarak gerekli işlevleri çağırır.
*/

void	expand_dollar(char **dst, char **src)
{
	char	*ptr;

	ptr = (*src) + 1;
	if (*ptr == *DOLLAR)
		double_dollar(dst, src);
	else if (*ptr == *QUSTION_MARK)
		question_mark(dst, src);
	else if (*ptr == ' ' || !*ptr || *ptr == *DOUBLE_QUOTE
		|| *ptr == *SINGLE_QUOTE)
		single_dollar(dst);
	else
		expand_dollar_value(dst, src);
}

/*
	Bu fonksiyonun amacı, belirtilen karakter dizisine
	yalnızca bir dolar işareti "$" eklemektir.
*/

void	single_dollar(char **dst)
{
	str_addchar(dst, *DOLLAR);
}

/*
	$ işaretinden sonra bir başka $ işareti bulunduğunda çağrılır.
	(++) diğer karaktere geçmeyi sağlar.
*/

void	double_dollar(char **dst, char **src)
{
	char	*line;

	line = ft_itoa(g_core.exit_status);
	own_strjoin(dst, line);
	free(line);
	(*src)++;
}

/*
	$ işaretinden sonra ? işareti bulunduğunda çağırılır.
	Shellde ? karakteri, son yürütülen komutun çıkış durumu veya
	çıkış kodunu temsil eder.
*/

void	question_mark(char **dst, char **src)
{
	char	*line;

	line = ft_itoa(g_core.exec_output);
	own_strjoin(dst, line);
	free(line);
	(*src)++;
}

/*
	expand_envs ile $ işaretinden sonra gelen karakter dizisindeki tüm 
	çevresel değişkenleri (environment variable) genişletir.

	tanımlanan ptr $ işaretinden sonra gelen ilk karaktere işaret eder.
	Karakter boşluk veya tırnak işareti değilse veya bir $ işaretine rastlanmazsa,
	count değişkeni artırılır ve ptr işaretçisi bir sonraki karaktere ilerletilir. 
	$ işaretinden sonra gelen karakter dizisindeki karakter sayısını belirler.

	ft_strpcpy ile ptr'de $ işaretinden sonra gelen karakter dizisinin kopyası
	oluşturulur. Son olarak, expand_envs işlevi kullanılarak karakter dizisi genişletilir
	ve genişletilmiş karakter dizisi dst karakter dizisiyle birleştirilir.
*/

void	expand_dollar_value(char **dst, char **src)
{
	int		count;
	char	*ptr;

	count = 0;
	ptr = (*src) + 1;
	while (*ptr != ' ' && *(ptr) && *ptr != *DOUBLE_QUOTE
		&& *ptr != *SINGLE_QUOTE && *ptr != '$')
	{
		count++;
		ptr++;
	}
	ptr = ft_strpcpy(NULL, (*src) + 1, count);
	expand_envs(dst, ptr);
	free(ptr);
	*src += count;
}
