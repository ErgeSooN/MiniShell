/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RaiseFileError.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:33:13 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:33:13 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	raise_file_error -> bir dosya açma hatası oluştuğunda, dosyanın açılmamasını ve
	hata mesajının yazdırılmasını sağlar.
	Dosyanın dizin hatasını kontrol eder. 
	(") -> "-bash: : No such file or directory" hata mesajını yazdırır.
	($) -> belirsiz bir yönlendirmeye işaret eden "-bash: [dosya adı]: ambiguous redirect" 
	hata mesajını yazdırır.
	Dosya açma hatası oluştuğunda, file->fd, SSTDERR (standard error stream) değerine atanır
	ve *file_output da SSTDERR değerine eşitlenir.

	check_directory_error ->verilen dosya adının bir dizin olup olmadığını kontrol eder. 
	Eğer en az bir '/' karakteri varsa, ad bir dizin olarak kabul edilir ve hataya yol açar. 
	Eğer yoksa, ad bir dosya adı olarak kabul edilir ve işlem devam eder.
*/

int	check_directory_error(char *file_name)
{
	char	*temp_file_name;

	temp_file_name = file_name;
	while (file_name && *file_name)
	{
		if (*(file_name++) == '/')
		{
			print_error("-bash: ", temp_file_name, ": Is a directory\n");
			return (0);
		}
	}
	return (1);
}

int	raise_file_error(t_filelist *file, int *file_output)
{
	int		error;

	error = 0;
	if (!check_directory_error(file->filename))
		error = 1;
	if (!error && *file->filename == '\"')
	{
		error = 1;
		print_error("-bash: : No such file or directory\n", NULL, NULL);
	}
	else if (!error && *file->filename == '$')
	{
		error = 1;
		print_error("-bash: ", file->filename, ": ambiguous redirect\n");
	}
	if (!error)
		return (error);
	file->fd = SSTDERR;
	*file_output = file->fd;
	return (error);
}
