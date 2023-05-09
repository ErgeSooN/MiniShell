/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:31:55 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:31:55 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/minishell.h"

/*
	programın kullanıcı sinyali (CTRL + C gibi) alması durumunda çağrılır. Eğer g_core.cmd
	değeri henüz atanmamışsa (yani henüz bir komut çalıştırılmamışsa), programın kaynaklarını
	(free_core() fonksiyonunu çağırarak) serbest bırakır ve ardından programı exit(131) çağrısı
	ile sonlandırır.
*/

void	exit_signal_check(void)
{
	if (!g_core.cmd)
	{
		free_core();
		g_core.exit_status = 131;
		exit(131);
	}
}

/*
	Sinyal yakalama işlemini yapar ve kullanıcının sinyal aldığında programı güvenli bir
	şekilde sonlandırmasını sağlar.
	Sinyal numarasının 2 olması kullanıcının CTRL+C tuşlarına bastığı anlamına gelir.

	g_core.exit_status değişkeni, 130 değeri ile atanır. Bu değer, programın sinyal nedeniyle 
	sonlandırıldığını belirtmek için kullanılan bir değerdir.

	"\n" karakteri stdout'a yazdırılır, bu işlem kullanıcının konsoluna yeni satır ekler.

	Readline kitaplığı, rl_on_new_line fonksiyonu çağrısı ile yeni bir satırın başına dönülür.

	Konsol girdisi rl_replace_line("", 0) ile silinir ve Readline kitaplığına gösterilir.
	
	rl_redisplay() fonksiyonu, Readline kütüphanesi tarafından yeniden çizilmesi gereken bölgeyi
	yeniden çizer. Bu işlem, terminal ekranını doğru bir şekilde günceller.

*/

void	signals(int sig)
{
	if (sig == 2)
	{
		g_core.exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
