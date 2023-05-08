/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DupFunction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:56 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:56 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
	---ÇOK KARIŞIK, TEKRAR EDİLMESİ GEREKİYOR---
	create_dup -> Komutun girdi ve çıktı yönlendirmelerini gerçekleştirir.
	Girdi ve çıktı yönlendirmelerine göre dup2 fonksiyonunu kullanarak stdin ve
	stdout akışlarını uygun dosyalar veya dosya tanımlayıcılarıyla değiştirir.

	Eğer HERADOC tipi girdi yönlendirmesi durumunda, bir boru hattı oluşturulur ve heradoc_values 
	değeri bu boru hattının yazma ucuna yazılır. Ardından, boru hattının okuma ucundan stdin
	akışına bağlantı yapılır.

	Eğer SSTDERR (2) veya daha büyük bir değerse, o zaman bu, stdin yerine kullanılacak bir 
	dosya tanımlayıcısı olduğunu belirtir. Bu durumda, dup2 fonksiyonu kullanılarak stdin akışı,
	cmd_list->infile ile değiştirilir. Yani, komutun girdisi olan dosya, stdin yerine kullanılacaktır.
*/

/*
	Örneğin, eğer bir dosya yönlendirme işlemi ile ls -l komutunun çıktısını input.txt dosyasına yazdıysak,
	cmd_list->infile değeri, input.txt dosyasının dosya tanımlayıcısı olacaktır ve dup2 fonksiyonu kullanılarak 
	stdin akışı, input.txt dosyası ile değiştirilecektir. Böylece ls -l komutu, standart girdi yerine input.txt 
	dosyasından girdi alacaktır.
*/

/*
	Dup2 fonk. -> dup2 fonksiyonu, dosya tanımlayıcısını (oldfd) başka bir dosya tanımlayıcısı (newfd) ile değiştirir.
	Bu işlem, newfd'nin önceden açılmış olması halinde, önce bu dosya tanımlayıcısını kapatır ve ardından oldfd'yi
	newfd ile eşleştirir. Eğer newfd dosya tanımlayıcısı daha önceden açılmamışsa, oldfd dosya tanımlayıcısını newfd 
	ile eşleştirir.
*/

void	create_dup(t_cmdlist *cmd_list, int *fd, int fd_index)
{
	int	new_fd[2];

	if (cmd_list->infile == HERADOC)
	{
		pipe(new_fd);
		write(new_fd[1], cmd_list->heradoc_values,
			ft_strlen(cmd_list->heradoc_values));
		dup2(new_fd[0], 0);
		close (new_fd[1]);
		close(new_fd[0]);
	}
	else if (cmd_list->infile > SSTDERR)
		dup2(cmd_list->infile, 0);
	else if (fd && cmd_list != g_core.cmd_table)
		dup2(fd[fd_index - 2], 0);
	if (cmd_list->outfile > SSTDERR)
		dup2(cmd_list->outfile, 1);
	else if (fd && cmd_list->next)
		dup2(fd[fd_index + 1], 1);
	if (fd_index >= 0)
		clear_pipe(fd);
}
