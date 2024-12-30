/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process_thinking.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:56:09 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 04:56:47 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	__philo_thread_process_thinking(
		t_philo_member *const member)
{
	member->status = PHILO_STATUS_THINK;
	__philo_print_thinking(member->start_time, member->my_number);
	pthread_mutex_lock(&member->mtx);
	if (*member->exit_flag == PHILO_LOCK_TRUE || \
		member->status == PHILO_STATUS_DIE)
		return (1);
	return (0);
}
