/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process_sleeping.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 04:54:04 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 04:55:30 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__philo_thread_process_sleeping(
			t_philo_member *const member)
{
	member->status = PHILO_STATUS_SLEEP;
	__philo_print_sleeping(member->start_time, member->my_number);
	usleep(member->params->sleep);
}
