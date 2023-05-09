/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunExport.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:42 by ayaman            #+#    #+#             */
/*   Updated: 2023/05/09 16:36:32 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Bu fonksiyon tek argüman olarak kullanılırsa env gibi çevresel 
  değişkenleri sıralamak için kullanılır ama birden fazla asrgüman var ise
  çevresel değişken eklemek için kullanılır.
*/

void	run_export(t_cmdlist *cmd_node)
{
	int		array_len;
	char	**temp_path;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 1)
	{
		temp_path = cmd_node->path;
		while (*(++temp_path))
		{
			double_export_arg(*temp_path);
			g_core.exec_output = 0;
		}
	}
	else
	{
		single_export_arg(cmd_node);
		g_core.exec_output = 0;
	}
}

/*
  Bu fonksiyon çevresel değişkenleri sıralamak için kullanılan fonksiyondur.
  Eğer çevresel değişkenin içeriği yok ise çevresel değişkenin başlığını yazdıktan
  sonra bir sonraki satıra geçer. Fakat çevresel değişkenin içeriği varsa çift tırnak
  ekleyip env'nin içeriğini çıktı sağlar ve bunu tüm envlere uygular.
*/

void	single_export_arg(t_cmdlist *cmd_node)
{
	t_env	*env;

	env = g_core.env_table;
	while (env)
	{
		write(cmd_node->outfile, "declare -x ", 11);
		write(cmd_node->outfile, env->env_name, ft_strlen(env->env_name));
		if (!env->content)
		{
			write(cmd_node->outfile, "\n", 1);
			env = env->next;
			continue ;
		}
		write(cmd_node->outfile, "=\"", 2);
		write(cmd_node->outfile, env->content, ft_strlen(env->content));
		write(cmd_node->outfile, "\"\n", 2);
		env = env->next;
	}
}

/*
  Bu fonksiyon birden fazla argüman girilmiş ise kullanılır.
  Bu fonksiyonun amacı çevresel değişken eklemektir. env_arg_control
  fonksiyonunda gerekli kontroller yapıldıktan sonra eğer hatalı bir
  argüman girilmiş ise return döndürürlür. Eğer hatalı bir argüman girilmemiş ise
  get_env_name fonksiyonuna gidilir. Arg değişkenine env değişkeninin başlangıcı
  gönderildikten sonra kalan yerin ilk karakterinde '=' kontorlü yapılır. Eğer 
  env değiştirilebilir ise freeleme işlemi yapılıp fonksiyondan çıkılır. Eğer
  eşleşen yok ise add_newenv fonksiyonu ile çevresel değişkenlere ekleme yapılır.
*/

void	double_export_arg(char *env_cmd)
{
	char	*arg;
	int		is_equal;
	t_env	*env;
	char	*temp_envname;

	if (!env_arg_control(env_cmd))
		return ;
	temp_envname = get_env_name(env_cmd);
	arg = env_cmd + ft_strlen(temp_envname);
	is_equal = 0;
	if (*arg == '=')
		is_equal |= 1;
	if (change_env(temp_envname, ++arg, is_equal))
	{
		free(temp_envname);
		return ;
	}
	env = g_core.env_table;
	add_newenv(&env, env_cmd);
	if (!is_equal)
		update_env(env_cmd, NULL);
	free(temp_envname);
}

/*
  Bu fonksiyon tüm env'leri gezerek eğer eşleşen çevresel değişken var ise
  bunları update_env fonksiyonu ile değiştirir. Eğer eşleşen yok ise 0 döndürür.
*/

int	change_env(char *envname, char *arg, int is_equal)
{
	t_env	*env;

	env = g_core.env_table;
	while (env)
	{
		if (str_compare(envname, env->env_name))
		{
			if (is_equal)
				update_env(envname, arg);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
