/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:28:06 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:28:06 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
  bu fonksiyon artık ayrıştırdığımız argümanları çalıştırmaya başladığımız yer.
  Eğer pipe yok ise run_single_command fonksiyonuna, eğer pipe var ise run_multiple_command
  fonksiyonuna yönlendirme yapar.
*/

void	executer(void)
{
	if (!g_core.cmd_table)
		return ;
	else if (!g_core.cmd_table->next)
		run_single_command(g_core.cmd_table, NULL);
	else
		run_multiple_command(g_core.cmd_table);
}
