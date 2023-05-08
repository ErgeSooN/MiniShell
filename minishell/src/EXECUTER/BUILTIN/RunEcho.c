/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunEcho.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:27 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:27 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/* 
  Bu fonksiyon bizim echo yani çıktı almamızı sağlayan fonksiyondur.
  eğer '-n' parametresi var ise is_n parametresi 1 olur ve newline 
  bastırılmadan çıktı sağlanır. Eğer birden fazla yazdırılacak argüman
  var ise ikinci if sorgusunda space boşluğu bırakılıp while döngüsünde 
  yazdırma işlemi devam ettirilir.
*/

void	run_echo(t_cmdlist *cmd_node)
{
	char	**path;
	int		is_n;

	is_n = 0;
	path = &cmd_node->path[1];
	if (*path && str_compare(*path, "-n"))
	{
		is_n = 1;
		path++;
	}
	while (*path)
	{
		if (*path)
			write(cmd_node->outfile, *path, ft_strlen(*path));
		if (*(++path))
			write(cmd_node->outfile, " ", 1);
	}
	if (!is_n)
		write(cmd_node->outfile, "\n", 1);
	g_core.exec_output = 0;
}
