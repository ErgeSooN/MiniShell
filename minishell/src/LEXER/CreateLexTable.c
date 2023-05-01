/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CreateLexTable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:30:23 by bbolat            #+#    #+#             */
/*   Updated: 2023/05/01 10:44:40 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Include/minishell.h"

/*
  komut satırının ilk parçasını last_node düğümüne kopyalar ve
  komut satırını boşluk karakterinden sonraki kısma kaydırır.
*/

void	parse_cmd(char **cmd_line, t_lexlist *last_node)
{
	size_t	count;
	char	*holder_content;

	count = get_cmdlen(*cmd_line);
	holder_content = (char *)malloc(sizeof(char) * (count) + 1);
	last_node->content = holder_content;
	holder_content[count] = 0;
	while (count--)
		*(holder_content++) = *((*cmd_line)++);
}

/*
  Bu fonksiyonun amacı, komut satırını parçalara ayırmak ve
  bunları bir liste halinde saklamaktır. Bu şekilde komut satırını daha kolay işleyebilirsiniz.
*/

void	create_lexlist(char *cmdline, t_lexlist **lex_table)
{
	t_lexlist	*last_node;

	trim_spaces(&cmdline);
	if (!cmdline || !*cmdline)
		return ;
	last_node = add_new_lex_node(lex_table);
	parse_cmd(&cmdline, last_node);
	create_lexlist(cmdline, lex_table);
}
