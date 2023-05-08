/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunExit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:37 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:37 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Bu fonksiyon girilen tüm değerlerin numerik olup olmadığını 
  kontrol eder. Eğer numerik değilse 0 döndürür.
*/

int	is_all_numeric(char *text)
{
	while (text && *text)
	{
		if (!(*text >= '0' && *text <= '9'))
			return (0);
		text++;
	}
	return (1);
}

/*
  Bu fonksiyon bizim exit komutumuz için gerekli olan fonksiyondur.
  ilk başta get _array len ile argüman sayısını 1 den itibaren saymaya başladıktan sonra
  (exit'i saymamak için) if sorgusuna geliyor. Eğer exit dışında 1'den fazla
  fonksiyon girilmiş ise fazla argüman hatasına yönlendirme yapar.
  Eğer exit dışında 1 tane argüman girilmiş ise girilen sayımnın numerik olup olmadığını kontrol eder.
  Eğer numerik ise girilen numarayla çıkış işlemi yapılır.
  En sonunda freeleme işlemi yaptıktan sonra çıkış tamamlanır.

  ///// satır 67 freeleme işlemlerinde kaldık
*/

void	run_exit(t_cmdlist *cmd_node)
{
	int	array_len;

	array_len = get_array_len(&cmd_node->path[1]);
	if (array_len > 1)
	{
		print_error("bash: exit: too many arguments\n", NULL, NULL);
		g_core.exec_output = 1;
		return ;
	}
	else if (array_len == 1)
	{
		if (is_all_numeric(cmd_node->path[1]))
			g_core.exec_output = ft_atoi(cmd_node->path[1]);
		else
		{
			print_error("bash: exit: ",
				cmd_node->path[1], ": numeric argument required\n");
			g_core.exec_output = 255;
		}
	}
	else
		g_core.exec_output = 0;
	free_for_loop();
	free_core();
	exit(g_core.exec_output % 256);
}
