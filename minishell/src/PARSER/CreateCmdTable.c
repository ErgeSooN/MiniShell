/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateCmdTable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:32:06 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:32:06 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
	create_cmdtable-> shell programının bir komut satırında işlem yapmak 
	üzere gerekli olan komutların listesi olan bir komut tablosu oluşturur. 
	Her öğeyi inceleyerek, eğer öğe boru(pipe)karakteri ise, yeni bir
	komutun başlangıcını işaret eder. Kaç adet komut olacağını belirler.
	
	create_cmdtable_nodes -> belirli bir sayıda komut düğümü oluşturur. 
	Her bir komut düğümünün varsayılan değerlerini ayarlamak için fill_cmdtable_node
	işlevini kullanır.

	fill_cmdtable_node -> bir t_cmdlist yapısının varsayılan değerlerini ayarlar.
	Bu yapının üyeleri, bir komutun gerektirdiği özellikleri tutar.
	Örn - komut dosyasının tam yolu, dosyaların listesi, standart giriş/çıkış tanımlayıcıları gibi.
*/

/*
	pid-> İşlem kimliği (PID)-işlem yürütüldüğünde atanır
	infile-> Standart giriş dosyası tanımlayıcısı
	outfile-> Standart çıkış dosyası tanımlayıcısı
	cmd-> Komut satırı argümanları
	path-> Komut dosyasının tam yolu
	next-> Bir sonraki komut düğümüne işaretçi
	files-> İlgili dosyaların listesi
	heradoc_values-> Heredoc verilerinin listesi
*/

void	create_cmdtable(t_lexlist *lex_table)
{
	int		count;

	if (!lex_table)
		return ;
	count = 1;
	while (lex_table)
	{
		if (lex_table->type == SIGN_PIPE)
			count++;
		else if (lex_table->type != TEXT)
		{
			lex_table = lex_table->next;
			if (lex_table && lex_table->type == SIGN_PIPE)
				lex_table = lex_table->next;
			continue ;
		}
		lex_table = lex_table->next;
	}
	create_cmdtable_nodes(count);
}

void	fill_cmdtable_node(t_cmdlist *node)
{
	node->pid = -1;
	node->infile = SSTDIN;
	node->outfile = SSTDOUT;
	node->cmd = NULL;
	node->path = NULL;
	node->next = NULL;
	node->files = NULL;
	node->heradoc_values = NULL;
}

void	create_cmdtable_nodes(int count)
{
	t_cmdlist	*temp_cmdtable;

	if (!count)
		return ;
	g_core.cmd_table = (t_cmdlist *)malloc(sizeof(t_cmdlist));
	fill_cmdtable_node(g_core.cmd_table);
	temp_cmdtable = g_core.cmd_table;
	while ((--count))
	{
		temp_cmdtable->next = (t_cmdlist *)malloc(sizeof(t_cmdlist));
		fill_cmdtable_node(temp_cmdtable->next);
		temp_cmdtable = temp_cmdtable->next;
	}
}
