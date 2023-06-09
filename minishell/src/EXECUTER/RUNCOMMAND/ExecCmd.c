/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecCmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:28:17 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:28:17 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	exec_command -> Yürütülecek komutların işlenmesini sağlayan bir fonksiyon.
		cmd_node = Yürütülecek komutu yani bir komut satırının parçalarını (örneğin, ls -l /)
		ve bunların bir araya getirilmesi için kullanılacak işaretleri (örneğin, | veya ;) içerir.
		fd = Dosya tanımlayıcılarını içeren bir dizi. Komutun standart giriş, çıkış ve hata çıkış 
		dosyalarını yönlendirmek için kullanılır.
		fd_index = Dosya tanımlayıcıları için dizi indeksi. fd dizisindeki hangi 
		dosya tanımlayıcısının kullanılacağını belirler.
*/

void	exec_command(t_cmdlist *cmd_node, int *fd, int fd_index)
{
	char	*cmd;
	int		builtin_index;

	if (cmd_node && !cmd_node->cmd)
		return ;
	cmd = get_cmd(cmd_node->cmd);
	builtin_index = is_builtin(cmd);
	if (builtin_index)
		run_builtin(cmd_node, builtin_index, fd, fd_index);
	else
		run_execve(cmd_node, fd, fd_index);
}

/*
  Bu fonksiyon komut satırında genellikle dosya yolu belirttiği zaman 
  kullanılır. Son '/' karakterinden itibaren komut satırının sonuna kadar
  saymamızı sağlar.
*/

char	*get_cmd(char *cmd)
{
	int		command_len;

	command_len = 0;
	while (*cmd)
	{
		command_len++;
		if (*cmd == '/')
			command_len = 0;
		cmd++;
	}
	return (cmd - command_len);
}
