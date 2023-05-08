/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RunCd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayaman <ayaman@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:27:22 by ayaman            #+#    #+#             */
/*   Updated: 2023/01/19 13:27:22 by ayaman           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Include/minishell.h"

/*
  Bu fonksiyon bizim cd komutunun çalıştırılmaya başlandığı yerdir.
  İlk başta get_array_len fonksiyonu ile argüman sayısını aldığımız yerdir.
  Eğer ikiden fazla argüman var ise hata kodu döndürür. Eğer iki tane argüman var ise
  cd_double_arg fonksiyonuna gidilir ve 2. argüman olan dosya dizinine gitmaiz sağlanır.
  Eğer bir argüman var ise de HOME dizinine gitmemizi sağlar.
*/

void	run_cd(t_cmdlist *cmd_node)
{
	int		array_len;

	array_len = get_array_len(cmd_node->path);
	if (array_len > 2)
	{
		g_core.exec_output = 1;
		print_error("-bash: cd: too many arguments\n", NULL, NULL);
	}
	else if (array_len == 2)
		cd_double_arg(cmd_node);
	else
		cd_single_arg();
}

/*
  Bu fonksiyona sadece cd argümanı var ise girilir. Bu fonksiyon bizim 
  HOME dizinine gitmemizi sağlayan fonksiyondur. Eğer HOME dizini bulunmuyorsa
  error döndürüp 1 hatası döndürür. (istem çağrısının başarısız olduğunu ve 
  geri döndüğü hata kodunun 1 olduğunu gösterir)
*/

void	cd_single_arg(void)
{
	t_env	*temp_env;
	char	*content;

	temp_env = g_core.env_table;
	while (temp_env)
	{
		if (str_compare("HOME", temp_env->env_name))
		{
			content = temp_env->content;
			if (!content)
				return ;
			change_dir(content);
			return ;
		}
		temp_env = temp_env->next;
	}
	print_error("-bash: cd: HOME not set\n", NULL, NULL);
	g_core.exec_output |= 1;
}

/*
  Bu fonksiyon bizim dosya yolu belirttiğimiz zaman gelinen fonksiyondur.
  Eğer path geçerli değil ise hata kodu döndürülür ve fonksiyondan çıkılır.
*/

void	cd_double_arg(t_cmdlist *cmd_node)
{
	if (!change_dir(cmd_node->path[1]))
	{
		print_error("--bash: cd: ", cmd_node->path[1],
			": No such file or directory\n");
		g_core.exec_output = 1;
		return ;
	}
}

/*
  Bu fonksiyon bizim dizin değiştirmek için kullandığımız fonksiyondur.
  İlk başta getcwd fonksiyonu ile bulunmuş olduğumuz dizini old pwd fonksiynonuna 
  kopyalıyoruz ki eğer yeni dosya yolunda bir hata var ise elimizde bulunabilsin.
  daha sonra chdir fonksiyonu ile girilen dosya yoluna geçmemizi sağlarız eğer bir hata olur 
  ise -1 döndürür ve freeleme işlemi yapılır. Daha sonra update_pwd_from_export fonksiyonuna
  gelinir. Eğer çevresel değişken değiştirilebilmiş ise oldpwd çevresel değişkeni de değiştirilir.
  Eğer değiştirilemez ise delete_env fonksiyonu ile OLDENW değişkeni freelenir.
  */

int	change_dir(char *path)
{
	char	pwd[256];
	int		is_pwdaccess;
	char	*oldpwd;
	int		error;

	oldpwd = ft_strdup(getcwd(pwd, 256));
	error = chdir(path);
	if (error == -1)
	{
		if (oldpwd)
			free(oldpwd);
		return (0);
	}
	is_pwdaccess = update_pwd_from_export("PWD", getcwd(pwd, 256));
	if (is_pwdaccess)
		update_pwd_from_export("OLDPWD", oldpwd);
	else
		delete_env("OLDPWD");
	if (oldpwd)
		free(oldpwd);
	return (1);
}

/*
  Eğer çevresel değişken değiştirilemez ise if sorgusunun içerisine girilir
  ve eski konumu geri yazdırılır.
  Eğer değiştirilebilirse update env 0 döndüreceği için fonksiyon direkt 1 
  döndürür.
*/

int	update_pwd_from_export(char *pwd_name, char *pwd_content)
{
	t_env	*temp_env;
	char	*temp_pwd;

	if (!update_env(pwd_name, pwd_content))
	{
		temp_env = g_core.env_table;
		temp_pwd = NULL;
		own_strjoin(&temp_pwd, pwd_name);
		str_addchar(&temp_pwd, '=');
		own_strjoin(&temp_pwd, pwd_content);
		add_newenv(&temp_env, temp_pwd);
		free(temp_pwd);
		return (0);
	}
	return (1);
}
