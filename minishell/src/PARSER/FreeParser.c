/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FreeParser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:32:30 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:32:30 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
	Komut satırında verilen girdilerin ayrıştırılması sonucu oluşan ağaç yapısını 
	temizlemek için kullanılır. Fonksiyon, tüm t_cmdlist düğümlerini dolaşır ve her
	düğüm için ayrı ayrı bellekten tahsis edilmiş alanları serbest bırakır.
*/

void	free_parser(void)
{
	t_cmdlist	*parser;
	t_cmdlist	*temp_parser;

	parser = g_core.cmd_table;
	while (parser)
	{
		temp_parser = parser;
		parser = parser->next;
		free_filelist(temp_parser->files);
		if (temp_parser->path)
			free(temp_parser->path);
		if (temp_parser->heradoc_values)
			free(temp_parser->heradoc_values);
		free(temp_parser);
	}
	g_core.cmd_table = NULL;
}

/*
	Tüm dosya listesi düğümlerini dolaşır ve her düğüm için ayrı ayrı bellekten 
	tahsis edilmiş alanları serbest bırakır. Ayrıca, her düğümün fd özelliği STDERRden
	büyükse, yani dosya tanımlayıcı bir standart hata değilse, dosyayı kapatır.
*/

void	free_filelist(t_filelist *files)
{
	t_filelist	*temp_files;

	while (files)
	{
		temp_files = files;
		files = files->next;
		if (temp_files->fd > SSTDERR)
			close(temp_files->fd);
		free(temp_files);
	}
}
