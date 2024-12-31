/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process_eating.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:48:35 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 21:36:38 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * フォークを利用するための関数
 *
 * 1. t_philo_member *const -> 哲学者情報
 */
static void	process1_use_fork(
				t_philo_member *const member);

/**
 * フォークを手放すための関数
 *
 * 1. t_philo_member *const -> 哲学者情報
 */
static void	process2_release_fork(
				t_philo_member *const member);

int	__philo_thread_process_eating(
		t_philo_member *const member)
{
	int				res;

	member->status = PHILO_STATUS_EAT;
	process1_use_fork(member);
	pthread_mutex_unlock(member->master_mtx);
	res = gettimeofday(&member->eat_time, &member->timezone);
	if (*member->exit_flag == PHILO_LOCK_TRUE || res)
		return (1);
	__philo_print_taken_fork(member->start_time, member->my_number);
	__philo_print_eating(member->start_time, member->my_number);
	member->eat_count++;
	if (member->params->must_eat_count != -1 && \
		__philo_thread_process_get_min_eat_count(member->members) >= \
		member->params->must_eat_count)
	{
		*member->exit_flag = PHILO_LOCK_TRUE;
		return (1);
	}
	usleep(member->params->eat);
	if (*member->exit_flag == PHILO_LOCK_TRUE || \
		member->status == PHILO_STATUS_DIE)
		return (1);
	process2_release_fork(member);
	return (0);
}

void	process1_use_fork(
					t_philo_member *const member)
{
	member->fork = PHILO_FORK_FALSE;
	member->member->fork = PHILO_FORK_FALSE;
}

void	process2_release_fork(
		t_philo_member *const member)
{
	member->fork = PHILO_FORK_TRUE;
	member->member->fork = PHILO_FORK_TRUE;
}
