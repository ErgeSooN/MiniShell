/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunCommand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:28:29 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:28:29 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  bu fonksiyon bizim pipe dan dolayı birden fazla argümanı çalışmamızı 
  sağlayan fonksiyonun başlangıcıdır. Bu fonksiyon cmd list devam ettiği
  sürece çalışır. Eğer cmd_list'i forkladıktan sonra child_process'i 
  run_process fonksiyonuna göndeririz.
*/

void	run_multiple_command(t_cmdlist *cmd_list)
{
	int			*fd;

	fd = create_pipe();
	while (cmd_list)
	{
		switch_pipe(&fd);
		pipe(&fd[2]);
		cmd_list->pid = fork();
		if (cmd_list->pid <= 0)
			run_process(cmd_list, fd, 2);
		cmd_list = cmd_list->next;
		if (fd[4] && fd[5])
		{
			close(fd[4]);
			close(fd[5]);
			fd[4] = 0;
			fd[5] = 0;
		}
	}
	clear_pipe(fd);
	wait_all();
}

/*
	Görevi tek bir komutu çalıştırmaktır. "infile" ve "outfile"
	girdi ve çıktı dosyalarının hangi dosya tanımlayıcılarına(fd) bağlanacağını 
	belirler.
	Eğer her ikisi de "SSTDERR" olarak ayarlanmamışsa "exec_command" 
	fonksiyonu çağrılır.

	exec_command'da son parametre olan "-1", yürütülen komutun standart hata 
	akışını gösterir. Bu değer "-1" iken yürütülen komut bir hata verirse, 
	hata mesajı standart çıktı akışında görünecektir. Eğer "-1" yerine başka 
	bir sayı verilirse, o sayıya karşılık gelen dosya tanımlayıcısı standart
	hata akışını temsil eder ve hata mesajları o dosya tanımlayıcısına 
	yönlendirilir.
*/

void	run_single_command(t_cmdlist *cmd_list, int *fd)
{
	if (cmd_list->infile != SSTDERR && cmd_list->outfile != SSTDERR)
		exec_command(cmd_list, fd, -1);
}
