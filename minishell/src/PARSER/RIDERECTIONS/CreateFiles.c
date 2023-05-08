/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateFiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:32:48 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:32:48 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	create_files -> t_cmdlist yapısındaki her bir komut için dosya oluşturma 
	işlemlerini yapar.
*/

void	create_files(t_cmdlist *node)
{
	t_filelist	*temp_file;

	if (!node)
		return ;
	run_heradocs(node);
	if (g_core.exec_output || !node)
		return ;
	while (node)
	{
		temp_file = node->files;
		while (temp_file)
		{
			if (*temp_file->metachar == *SINGLE_GREAT)
				create_outfile(node, temp_file);
			else
				create_infile(node, temp_file);
			if (temp_file->fd == SSTDERR)
			{
				g_core.exec_output = 1;
				break ;
			}
			temp_file = temp_file->next;
		}
		node = node->next;
	}
}
