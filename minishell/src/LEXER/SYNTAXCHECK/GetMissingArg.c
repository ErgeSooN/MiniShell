/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GetMissingArg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:31:19 by bbolat            #+#    #+#             */
/*   Updated: 2023/05/03 23:52:34 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  
*/

char	*get_missing_arg(void)
{
	char	*ptr;
	int		fd[2];
	char	c[1];

	pipe(fd);
	if (!read_missing_arg(fd))
		return (NULL);
	ptr = NULL;
	while (read(fd[0], c, 1))
		str_addchar(&ptr, *c);
	close(fd[0]);
	return (ptr);
}

int	read_missing_arg(int *fd)
{
	int		pid;
	int		return_value;

	pid = fork();
	if (!pid)
		read_missing_arg_value(fd);
	close(fd[1]);
	waitpid(pid, &return_value, 0);
	return_value = WEXITSTATUS(return_value);
	if (return_value == SIGNAL_C)
	{
		close(fd[0]);
		free_for_loop();
		return (0);
	}
	return (1);
}

/*
	Bu fonksiyon, bir dosya tanımlayıcısı (file descriptor) dizisi alan bir işlevdir. 
	Dizinin ilk elemanı, verilerin okunacağı dosyanın tanımlayıcısıdır ve ikinci elemanı, 
	verilerin yazılacağı dosyanın tanımlayıcısıdır. Fonksiyon, öncelikle yazma işlemi için 
	kullanılan dosya tanımlayıcısını kapatır ve sonra sonsuz bir döngüye girer. Döngü içinde, 
	kullanıcıdan bir girdi alınır ve bu girdi bir dizi doğrulama işleminden geçirilir. 
	Eğer girdi geçerliyse, veriler yazılacak olan dosyanın tanımlayıcısına yazılır ve yazma işlemi tamamlanır. 
	Ardından, dosya tanıml+ayıcısı kapatılır, kullanıcının girdisi kaydedilir ve bellekten serbest bırakılır. 
	Son olarak, döngüden çıkılır ve program başarıyla sonlandırılır.
*/

void	read_missing_arg_value(int *fd)
{
	char	*ptr;

	close(fd[0]);
	while (1)
	{
		ptr = readline("> ");
		if (!control_valid_arg(ptr))
			continue ;
		write(fd[1], ptr, ft_strlen(ptr));
		close(fd[1]);
		add_history(ptr);
		free(ptr);
		free_for_loop();
		free_core();
		exit(EXIT_SUCCESS);
	}
}

/*Eğer argüman bulunmuyorsa freeleyip fonksiyondan çıkılır.*/

int	control_valid_arg(char *ptr)
{
	char	*str;

	if (!ptr)
		return (0);
	str = ptr;
	trim_spaces(&str);
	if (!*str)
	{
		free(ptr);
		return (0);
	}
	return (1);
}
