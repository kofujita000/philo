/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:22:29 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/15 21:45:20 by kofujita         ###   ########.fr       */
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
 * お亡くなり処理関数
 *
 * 1. t_philo_member *const -> 哲学者情報
 */
static void	process2_die(
				t_philo_member *const member);

/**
 * フォークを手放すための関数
 *
 * 1. t_philo_member *const -> 哲学者情報
 */
static void process3_release_fork(
				t_philo_member *const member);

void	*__philo_thread_process(
			t_philo_member *const member)
{
	int				res;

	while (1)
	{
		member->status = PHILO_STATUS_THINK;
		__philo_print_thinking(member->start_time, member->my_number);
		pthread_mutex_lock(&member->mtx);
		if (member->status == PHILO_STATUS_DIE)
			break;
		member->status = PHILO_STATUS_EAT;
		process1_use_fork(member);
		pthread_mutex_unlock(member->master_mtx);
		res = gettimeofday(&member->eat_time, &member->timezone);
		if (res)
			break;
		__philo_print_taken_fork(member->start_time, member->my_number);
		__philo_print_eating(member->start_time, member->my_number);
		usleep(member->params->eat);
		if (member->status == PHILO_STATUS_DIE)
			break;
		process3_release_fork(member);
		__philo_print_sleeping(member->start_time, member->my_number);
		usleep(member->params->sleep);
		if (member->status == PHILO_STATUS_DIE)
			break;
	}
	process2_die(member);
	return (NULL);
}

void	process1_use_fork(
					t_philo_member *const member)
{
	printf("member_my_number begin: %d\n", member->my_number);
	member->fork = PHILO_FORK_FALSE;
	member->member->fork = PHILO_FORK_FALSE;
	printf("member_my_number end: %d\n", member->my_number);
}

void	process2_die(
			t_philo_member *const member)
{
	member->status = PHILO_STATUS_DIE;
	pthread_mutex_unlock(member->master_mtx);
}

void process3_release_fork(
		t_philo_member *const member)
{
	member->fork = PHILO_FORK_TRUE;
	member->member->fork = PHILO_FORK_TRUE;
}
