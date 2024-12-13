/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 09:50:57 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/14 00:20:26 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 哲学者の順番情報を初期化するための関数
 *
 * r. t_philo_sequential -> [!NULL => 初期化失敗]
 *                          [NULL  => 初期化成功]
 */
static t_philo_sequential	*process1_init_sequential(void);

/**
 * 哲学者のリスト情報を初期化するための関数
 *
 * 1. t_philo_member *const -> メンバーのアドレス (配列の先頭というわけではない)
 *
 * r. t_philo_list* -> [!NULL => 初期化失敗]
 *                     [NULL  => 初期化成功]
 */
static t_philo_list			*process2_init_list(
								t_philo_member *const member_addr);

/**
 * リスト情報を順番情報に設定するための関数
 *
 * 1. t_philo_sequential *const -> 順番情報群
 * 2. t_philo_list       *const -> 代入情報
 */
void						process3_add_list_for_sequential(
								t_philo_sequential *const seq,
								t_philo_list *const lst);

t_philo_sequential	*t_philo_sequential_init(
						const t_philo_members *const members)
{
	size_t				cnt;
	t_philo_list		*buf;
	t_philo_sequential	*ret;

	ret = process1_init_sequential();
	if (!ret)
		return (ret);
	cnt = 0;
	while (cnt != members->size)
	{
		buf = process2_init_list(&members->data[cnt++]);
		if (!buf)
			return (t_philo_sequential_free(ret), NULL);
		process3_add_list_for_sequential(ret, buf);
	}
	t_philo_sequential_move_current_to_begin(ret);
	return (ret);
}

t_philo_sequential	*process1_init_sequential(void)
{
	t_philo_sequential	*ret;

	ret = (t_philo_sequential *)malloc(sizeof(t_philo_sequential));
	if (!ret)
		return (ret);
	ret->before = NULL;
	ret->end = NULL;
	ret->begin = NULL;
	ret->current = NULL;
	return (ret);
}

t_philo_list	*process2_init_list(
					t_philo_member *const member_addr)
{
	t_philo_list		*ret;

	ret = (t_philo_list *)malloc(sizeof(t_philo_list));
	if (!ret)
		return (NULL);
	ret->data = member_addr;
	ret->next = NULL;
	return (ret);
}

void	process3_add_list_for_sequential(
			t_philo_sequential *const seq,
			t_philo_list *const lst)
{
	if (!seq->begin)
	{
		seq->begin = lst;
		seq->current = lst;
	}
	else
	{
		seq->current->next = lst;
		seq->before = seq->current;
		seq->current = lst;
	}
	seq->end = lst;
}
