/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunPwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:47 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:47 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

void	run_pwd(t_cmdlist *cmd_node)
{
	char	cwd[256];
	char	*pwd;

	pwd = getcwd(cwd, 256);
	write(cmd_node->outfile, pwd, ft_strlen(pwd));
	write(cmd_node->outfile, "\n", 1);
}
