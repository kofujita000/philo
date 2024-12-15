/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 20:59:55 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/15 20:43:44 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	__philo_die_process(
			t_philo_info *const info,
			t_philo_member *const member)
{
	int		res;

	pthread_mutex_unlock(&member->mtx);
	res = t_philo_sequential_is_end(info->sequential);
	t_philo_sequential_erase(info->sequential);
	if (res)
		t_philo_sequential_move_current_to_begin(info->sequential);
}
