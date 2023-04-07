/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbolat <bbolat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:26:35 by bbolat            #+#    #+#             */
/*   Updated: 2023/01/19 13:26:35 by bbolat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "tables.h"
# include "macros.h"

//MAIN
void	expander(void);

//EXANDTEXT
void	expand_values_from_lexlist(void);
void	expand_text(t_lexlist *lex_table, int is_after_meta);

void	expand_order(char **dst, char **src);
void	expand_envs(char **dst, char *ptr);

void	expand_dollar(char **dst, char **src);
void	single_dollar(char **dst);
void	double_dollar(char **dst, char **src);
void	question_mark(char **dst, char **src);
void	expand_dollar_value(char **dst, char **src);

void	clear_void_contents(void);

//EXPANDCMD
void	expand_cmd(char **dst);
void	expand_from_env_value(char **dst, char *content);
char	*get_arg_from_env_value(char **envs, char *search_arg_name);

#endif
