/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InitDestroyHeradocFile.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:33:03 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:33:03 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
	
Heredoc okumak için açılan dosyanın kapatılmasını sağlar. Eğer dosya açıksa, dosyanın
dosya tanımlayıcısı kapatılır ve heredoc okuma işlemi sonlandırılır. Fonksiyon ayrıca
g_core.heradoc_fd değişkeninin değerini sıfırlar.
*/

void	close_heradoc_file(void)
{
	if (g_core.heradoc_fd > SSTDERR)
	{
		g_core.heradoc_fd = close(g_core.heradoc_fd);
		g_core.heradoc_fd = 0;
	}
}

/*
	Fonksiyon oluşturulacak dosyanın açılması için kullanılır.
	ptr, getcwd ile geçerli çalışma dizini yolunu depolamak için bir 
	arabellek olarak kullanılır.
	own_strjoin ve str_addchar kullanılarak, heracoc_path değişkenine geçerli 
	dizin yolu ve "heradoc" dosya adı eklenir.
	create_mode değişkeninin değeri ile "READ" karşılaştırması yapar ve sonuca 
	göre dosyanın okuma veya yazma modunda açılacağını belirler.

	Eğer create_mode değişkeni "READ" ise, open fonksiyonu O_RDONLY modunda açılır ve 
	g_core.heradoc_fd değişkenine dosya tanımlayıcısı atanır. 
	Aksi takdirde, open fonksiyonu O_WRONLY | O_CREAT | O_TRUNC modunda açılır, dosya yoksa 
	oluşturulur ve dosyanın içeriği silinir.

	0777 -> dosya sisteminde dosya ya da dizinlerin erişim izinlerini belirler. 
	Bu sayı dosyanın veya dizinin tüm erişim haklarının açık olduğunu gösterir.

*/

void	open_heradoc_file(char	*create_mode)
{
	char	*heracoc_path;
	char	ptr[256];

	heracoc_path = NULL;
	own_strjoin(&heracoc_path, (char *)getcwd(ptr, 256));
	str_addchar(&heracoc_path, '/');
	own_strjoin(&heracoc_path, "heradoc");
	if (str_compare(create_mode, "READ"))
		g_core.heradoc_fd = open(heracoc_path, O_RDONLY, 0777);
	else
		g_core.heradoc_fd = open(heracoc_path,
				O_WRONLY | O_CREAT | O_TRUNC, 0777);
	free(heracoc_path);
}
