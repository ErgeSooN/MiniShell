/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PipeFunction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:28:23 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:28:23 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Bu fonksiyon bizim 6'lık integer yer açtığımız yerdir.
  Bu fonksiyonun amacı pipe ile aldığımız argümanların
  input ve outputlarını birbirine bağlamak diyebiliriz.
*/

int	*create_pipe(void)
{
	int		index;
	int		*fd;

	fd = (int *)malloc(sizeof(int) * 6);
	index = -1;
	while (++index < 6)
		fd[index] = 0;
	return (fd);
}

/*
  Bu fonksiyon bizim input ve outputların yeri değiştikten
  sonra içlerini sıfırlayıp close fonksiyonu ile kapatmamızı 
  sağlayan fonksiyondur.
*/

void	clear_pipe(int *fd)
{
	int	index;

	if (fd)
	{
		index = -1;
		while (++index < 6)
		{
			if (fd[index])
				close(fd[index]);
		}
		free(fd);
	}
}

/*
  Bu fonksiyon bizim bitler arası yer değiştirme yaptığımız
  asıl yerdir. Bu fonksiyonun amacı birden fazla pipe fonksiyonu 
  varsa sürekli yer değiştirerek diğer pipeları da 6 bitlik yere almamızı
  sağlar.
*/

void    switch_pipe(int **fd)
{
    int temp;

    temp = (*fd)[0];
    (*fd)[0] = (*fd)[2];
    (*fd)[2] = temp;

    temp = (*fd)[1];
    (*fd)[1] = (*fd)[3];
    (*fd)[3] = temp;

    temp = (*fd)[5];
    (*fd)[5] = (*fd)[3];
    (*fd)[3] = temp;

    temp = (*fd)[2];
    (*fd)[2] = (*fd)[4];
    (*fd)[4] = temp;
}
