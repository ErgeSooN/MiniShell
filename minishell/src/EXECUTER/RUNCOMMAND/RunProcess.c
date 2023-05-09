/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunProcess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:28:42 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:28:42 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Bu fonksiyon argümanların çalıştırılmaya balandığı yerin başlangıcıdır
  
*/

void	run_process(t_cmdlist *cmd_list, int *fd, int fd_index)
{
	if (cmd_list->infile != SSTDERR && cmd_list->outfile != SSTDERR)
		exec_command(cmd_list, fd, fd_index);
	else
		clear_pipe(fd);
	free_for_loop();
	free_core();
	exit(g_core.exec_output);
}

/*
	Paralel olarak yürütülen tüm işlemleri beklemek ve çıkış durumlarını 
	işlemek için kullanılır.Her bir komutun işlemi tamamlanana kadar bekleme 
	işlemi yapar. Eğer komut zinciri içinde son komut ise, çıkış durumu 
	"g_core.exec_output" değişkeninde tutulur. Eğer son komut değilse, çıkış 
	durumu görmezden gelinir.

	"waitpid" fonksiyonunu kullanarak, child_processin (yürütülen komut) 
	tamamlanmasını bekler. İlk parametre olarak "cmd_list->pid" kullanılır ve bu,
	bekleme yapılacak olan child_processin kimliğidir. İkinci parametre "0"ayarlanır,
	çünkü bekleme sırasında hiçbir ek bilgiye ihtiyaç duyulmaz. Üçüncü parametre 
	"0" kullanılır, çünkü beklemeyi engelleyen herhangi bir sinyal olmadığından emin olunur.
*/

/*
	waitpid(pid, status, options);
	waitpid(child_p pid, child_p durumu-örn null olursa durum bilgisi döndürmez-, bekleme davranışları)

	WEXİTSTATUS -> kullanıcının programın başarılı bir şekilde çalıştığını veya
	bir hatayla karşılaştığını anlamasına yardımcı olur.
	g_core.exec_output'ta işlem çıkış durumunu saklar. Bu işlem çıkış 
	durumu, son çalıştırılan komutun çıkış durumunu temsil eder. Bu çıkış durumu, 
	genellikle 0 (başarılı) veya farklı bir değer (hata durumu) olacaktır.
*/

void	wait_all(void)
{
	t_cmdlist	*cmd_list;

	cmd_list = g_core.cmd_table;
	while (cmd_list)
	{
		if (!cmd_list->next)
			waitpid(cmd_list->pid, &g_core.exec_output, 0);
		else
			waitpid(cmd_list->pid, 0, 0);
		cmd_list = cmd_list->next;
	}
	g_core.exec_output = WEXITSTATUS(g_core.exec_output);
}
