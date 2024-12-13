/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_ovserver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 21:42:07 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/14 01:20:41 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * スレッド処理関数
 *
 * 1. t_philo_info *const -> 情報を保持する構造体
 */
static void	*process1_ovserver(
				t_philo_info *const info);

/**
 * 死亡を確認するための関数
 *
 * 1. t_philo_info *const   -> 情報を保持する構造体
 * 2. long                  -> 現在のミリ秒
 * 3. t_philo_member *const -> メンバの配列先頭アドレス
 */
static void	process2_check_die(
				t_philo_info *const info,
				long ms,
				t_philo_member *const members);

t_philo_code	__philo_run_die_ovserver(
					t_philo_info *const info)
{
	int		res;

	res = pthread_create(&info->die_ovserver_ptid, NULL, \
			(void *(*)(void *))process1_ovserver, info);
	if (res)
		return (PHILO_ERROR_START_DIE_OVSERVER);
	return (PHILO_SUCCESS);
}

void	*process1_ovserver(
			t_philo_info *const info)
{
	struct timeval	tv;
	long			ts;

	while (info->die_ovserver_flag)
	{
		gettimeofday(&tv, NULL);
		ts = tv.tv_sec * 1000 + (tv.tv_usec / 1000);
		process2_check_die(info, ts, info->members->data);
	}
	return NULL;
}

void	process2_check_die(
			t_philo_info *const info,
			long ms,
			t_philo_member *const members)
{
	size_t			cnt;
	long			buf;

	cnt = -1;
	while (++cnt != info->members->size)
	{
		if (members[cnt].status == PHILO_STATUS_DIE)
			continue ;
		buf = members[cnt].eat_time.tv_sec * 1000 + \
			(members[cnt].eat_time.tv_usec / 1000);
		if (buf + info->parms.die < ms)
		{
			members[cnt].status = PHILO_STATUS_DIE;
			__philo_print_died(members[cnt].my_number);
		}
	}
}
