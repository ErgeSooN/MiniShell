/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetArrayLen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:36:47 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:36:47 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  girilen argümanların sayısını bulmamızı sağlayan fonksiyondur.
*/

int	get_array_len(char **array)
{
	int	count;

	count = 0;
	while (array && *(array++))
		count++;
	return (count);
}
