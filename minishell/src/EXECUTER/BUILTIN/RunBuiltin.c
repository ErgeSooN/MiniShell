/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunBuiltin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:16 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:16 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Bu fonksiyon bizim terminale girilen argümanın kıyaslamasını
  yaptığımız fonksiyondur. Eşleşmeye göre macrolarda tanımladığımız
  komutu döndürmemizi sağlar.
*/

int	is_builtin(char *cmd)
{
	if (str_compare(cmd, "echo"))
		return (ECHO);
	else if (str_compare(cmd, "cd"))
		return (CD);
	else if (str_compare(cmd, "pwd"))
		return (PWD);
	else if (str_compare(cmd, "export"))
		return (EXPORT);
	else if (str_compare(cmd, "unset"))
		return (UNSET);
	else if (str_compare(cmd, "env"))
		return (ENV);
	else if (str_compare(cmd, "exit"))
		return (EXIT);
	return (0);
}

/*
  Bu fonksiyon bizim komutları çalıştırmak için yönlendirme yaptığımız yerdir.
  ilk baştaki if sorgusuna eğer pipe karkateri var ise girilir.
*/

void	run_builtin(t_cmdlist *cmd_node, int builtin, int *fd, int fd_index)
{
	if (fd)
		create_dup(cmd_node, fd, fd_index);
	if (builtin == ECHO)
		run_echo(cmd_node);
	else if (builtin == CD)
		run_cd(cmd_node);
	else if (builtin == PWD)
		run_pwd(cmd_node);
	else if (builtin == EXPORT)
		run_export(cmd_node);
	else if (builtin == UNSET)
		run_unset(cmd_node);
	else if (builtin == ENV)
		run_env(cmd_node);
	else if (builtin == EXIT)
		run_exit(cmd_node);
}
