/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OutFile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbolat <bbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:33:07 by bbolat            #+#    #+#             */
/*   Updated: 2023/01/19 13:33:07 by bbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	create_outfile -> node yapısında verilen outfile dosyasının yolunu oluşturmak 
	ve dosyayı açmak için kullanılır. Dosya yolu, mevcut çalışma dizininin 
	(current working directory(CWD))başına '/' karakteri ekleyerek ve dosya adını da 
	ekleyerek oluşturulur. Dosya metacharacter'ı DOUBLE_GREAT ise dosya açılır.
	O_APPEND bayrağı -> dosyanın sonuna eklenmesi gerektiğini belirtir 
	O_TRUNC bayrağı -> dosyayı üzerine yazacak şkeilde açılmasını belirtir.
	node->outfile değeri, açılan dosyanın dosya tanımlayıcısı (fd) ile güncellenir.
*/

void	create_outfile(t_cmdlist *node, t_filelist *file)
{
	char	*outfile_path;
	char	ptr[256];

	if (raise_file_error(file, &node->outfile))
		return ;
	outfile_path = NULL;
	own_strjoin(&outfile_path, (char *)getcwd(ptr, 256));
	str_addchar(&outfile_path, '/');
	own_strjoin(&outfile_path, file->filename);
	if (file->metachar[1] == DOUBLE_GREAT[1])
		file->fd = open(outfile_path,
				O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file->fd = open(outfile_path,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	node->outfile = file->fd;
	free(outfile_path);
}
