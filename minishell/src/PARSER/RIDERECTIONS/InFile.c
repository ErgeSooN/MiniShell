/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InFile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbolat <bbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:32:58 by bbolat            #+#    #+#             */
/*   Updated: 2023/01/19 13:32:58 by bbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	create_infile -> girdi dosyası bağlantısı oluşturur. getcwd fonksiyonu çağrılarak 
	geçerli çalışma dizininin adı alınır ve dosya adı ile birleştirilir. Dosya adı ve
	yolunun tam adı pwd'de saklanır. Erişim kontrolü yapılır ve dosyanın varlığı kontrol 
	edilir. O_RDONLY flag'iyle açılır ve file->fd'ye atanır. Dosya mevcut değilse 
	hata mesajı yazdırılır.
*/

void	create_infile(t_cmdlist *node, t_filelist *file)
{
	char	*pwd;
	char	ptr[256];

	if (file->metachar[1] == DOUBLE_LESS[1])
	{
		node->infile = HERADOC;
		return ;
	}
	if (raise_file_error(file, &node->infile))
		return ;
	pwd = NULL;
	own_strjoin(&pwd, (char *)getcwd(ptr, 256));
	str_addchar(&pwd, '/');
	own_strjoin(&pwd, file->filename);
	if (!access(pwd, F_OK))
		file->fd = open(pwd, O_RDONLY, 0777);
	if (file->fd <= SSTDERR && file->fd != HERADOC)
	{
		print_error("-bash: ", file->filename,
			": No such file or directory\n");
		g_core.exec_output = 1;
		file->fd = SSTDERR;
	}
	node->infile = file->fd;
	free(pwd);
}
