/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:22:29 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 04:57:23 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * お亡くなり処理関数
 *
 * 1. t_philo_member *const -> 哲学者情報
 */
static void	process1_die(
				t_philo_member *const member);

void	*__philo_thread_process(
			t_philo_member *const member)
{
	while (*member->exit_flag == PHILO_LOCK_FALSE && \
			member->status != PHILO_STATUS_DIE)
	{
		if (__philo_thread_process_thinking(member))
			break ;
		if (__philo_thread_process_eating(member))
			break ;
		__philo_thread_process_sleeping(member);
	}
	process1_die(member);
	return (NULL);
}

void	process1_die(
			t_philo_member *const member)
{
	member->status = PHILO_STATUS_DIE;
	pthread_mutex_unlock(member->master_mtx);
}
