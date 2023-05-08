/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:31:33 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:31:33 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

void	free_core(void)
{
	free_metachars();
	free_envtable();
	rl_clear_history();
}

/*
	önce g_core.cmd değişkeninin hafızada bir yer tutup tutmadığını kontrol eder ve 
	eğer öyleyse bu bellek alanını serbest bırakır. Ardından, lexer ve parser yapıları 
	için ayrılan bellek alanlarını serbest bırakan free_lexer() ve free_parser() 
	fonksiyonlarını çağırır. Son olarak, heredoc dosyası kapalıysa dosya tanıtıcısını 
	kapatmak için close_heradoc_file() fonksiyonunu çağırır.
*/

void	free_for_loop(void)
{
	if (g_core.cmd)
	{
		free(g_core.cmd);
		g_core.cmd = NULL;
	}
	if (g_core.lex_table)
		free_lexer();
	if (g_core.cmd_table)
		free_parser();
	close_heradoc_file();
}
