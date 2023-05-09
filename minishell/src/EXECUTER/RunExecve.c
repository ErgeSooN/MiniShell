/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunExecve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:28:01 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:28:01 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
	run_execve -> fork ile child_process oluşturur. Execve işlevi çağrılır ve yeni
	bir program dosyası yüklenir. Bu işlem, mevcut işlemi değiştirir ve yüklenen
	programın işlevleri çalıştırılır.

	create_dup -> Mevcut işlemin dosya tanımlayıcıları kopyalanır. Bu işlem, 
	giriş/çıkış yönlendirmesi veya boru hatları gibi işlemleri gerçekleştirmek için kullanılır.
	
	get_env_cpy -> Mevcut ortamın bir kopyası alınır. Bu kopya, execve() işlevi 
	tarafından kullanılacak olan ortam listesi olarak kullanılır.

	*execve == -1 olursa program dosyası yüklenemediği anlamına gelir. Hata mesajı
	yazdırılarak bellek alanları serbest bırakılıp exit ile program sonlandırılır.
	127 hata kodu yüklenen program dosyasının bulunamaması durumunda kullanılır.

	Son if bloğu child processin işlemi tamamlamasını ve çıkış durumunu raporlamasını
	beklemek için kullanılır. waitpid(), child processin işlem tamamlama durumunu bekleyen
	parent processe bilgi verir. parent_process bu bilgiyi g_core.exec_output değişkenine atar.
	wexitstatus -> bir işlem tamamlanana kadar child_processin çıkış durumunu beklemek için kullanılır. 
*/

void	run_execve(t_cmdlist *cmd_node, int *fd, int fd_index)
{
	char	**envlist;

	cmd_node->pid = fork();
	if (!cmd_node->pid)
	{
		create_dup(cmd_node, fd, fd_index);
		envlist = get_env_cpy();
		if (execve(cmd_node->cmd, cmd_node->path, envlist) == -1)
		{
			if (cmd_node->cmd)
				print_error(cmd_node->cmd, " command not found\n", NULL);
			free_env_cpy(envlist);
			free_for_loop();
			free_core();
			exit(127);
		}
	}
	if (fd && cmd_node->pid)
		clear_pipe(fd);
	waitpid(cmd_node->pid, &g_core.exec_output, 0);
	g_core.exec_output = WEXITSTATUS(g_core.exec_output);
}
