/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taken_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 19:25:54 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/15 20:03:09 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__philo_print_taken_fork(
			const long start_time,
			const int32_t my_number)
{
	struct timeval	tv;
	long			timestamp;

	gettimeofday(&tv, NULL);
	timestamp = tv.tv_sec * 1000 + tv.tv_usec / 1000 - start_time;
	printf(PHILO_MSG_TAKEN_FORK, timestamp, my_number);
}
