/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:28:43 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 04:40:15 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * 左右のメンバ情報を取得するための関数
 *
 * 1. const t_philo_info *const   -> 情報を保持する構造体
 * 2. const t_philo_member *const -> 対象メンバ情報
 * 3. t_philo_member **const      -> 対象メンバの左隣のアドレス
 * 4. t_philo_member **const      -> 対象メンバの右隣のアドレス
 *
 * r. t_philo_code -> [PHILO_SUCCESS   => 処理成功]
 *                    [PHILO_NONE_SIDE => 隣にメンバがいない]
 */
static t_philo_code	process1_set_left_and_right(
						const t_philo_info *const info,
						const t_philo_member *const member,
						t_philo_member **const left,
						t_philo_member **const right);

/**
 * 左右のメンバのどちらのフォークを利用するかを調べる関数
 *
 * 1. t_philo_member *const -> 対象メンバ情報
 * 2. t_philo_member *const -> 対象メンバの左隣のアドレス
 * 3. t_philo_member *const -> 対象メンバの右隣のアドレス
 *
 * r. t_philo_code -> [PHILO_SUCCESS => 処理成功]
 *                    [PHILO_USED_FORK => フォークがなかった]
 */
static t_philo_code	process2_select_fork_left_or_right(
						t_philo_member *const member,
						t_philo_member *const left,
						t_philo_member *const right);

t_philo_code	__philo_think_process(
					t_philo_info *const info,
					t_philo_member *const member)
{
	t_philo_code	res;
	t_philo_member	*left;
	t_philo_member	*right;

	if (member->fork == PHILO_FORK_FALSE)
		return (PHILO_NONE_SIDE);
	res = process1_set_left_and_right(info, member, &left, &right);
	if (res == PHILO_NONE_SIDE)
		return (res);
	res = process2_select_fork_left_or_right(member, left, right);
	if (res == PHILO_USED_FORK)
		return (res);
	pthread_mutex_lock(&info->mtx);
	pthread_mutex_unlock(&member->mtx);
	pthread_mutex_lock(&info->mtx);
	t_philo_sequential_move_end(info->sequential);
	pthread_mutex_unlock(&info->mtx);
	return (PHILO_SUCCESS);
}

t_philo_code	process1_set_left_and_right(
					const t_philo_info *const info,
					const t_philo_member *const member,
					t_philo_member **const left,
					t_philo_member **const right)
{
	size_t	size;

	size = info->members->size;
	if (size <= 1)
		return (PHILO_NONE_SIDE);
	if (member->my_number == 0)
		*left = &info->members->data[size - 1];
	else
		*left = &info->members->data[member->my_number - 1];
	if (member->my_number == (int32_t)(size - 1))
		*right = &info->members->data[0];
	else
		*right = &info->members->data[member->my_number + 1];
	return (PHILO_SUCCESS);
}

t_philo_code	process2_select_fork_left_or_right(
					t_philo_member *const member,
					t_philo_member *const left,
					t_philo_member *const right)
{
	if (left->fork == PHILO_FORK_FALSE && right->fork == PHILO_FORK_FALSE)
		return (PHILO_USED_FORK);
	if (left->fork == PHILO_FORK_TRUE && right->fork == PHILO_FORK_TRUE)
	{
		if (left->eat_time.tv_usec <= right->eat_time.tv_usec)
			member->member = right;
		else
			member->member = left;
	}
	if (left->fork == PHILO_FORK_TRUE)
		member->member = left;
	if (right->fork == PHILO_FORK_TRUE)
		member->member = right;
	if (member->member->eat_time.tv_sec < member->eat_time.tv_sec || \
		(member->member->eat_time.tv_sec == member->eat_time.tv_sec && \
		member->member->eat_time.tv_usec / 1000 < \
		member->eat_time.tv_usec / 1000))
		return (PHILO_USED_FORK);
	return (PHILO_SUCCESS);
}
