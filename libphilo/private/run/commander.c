/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:34:12 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 02:57:27 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_code	__philo_run_commander(
					t_philo_info *const info)
{
	t_philo_code		res;
	const t_philo_list	*current_list;

	while (info->exit_flag == PHILO_LOCK_FALSE)
	{
		usleep(10);
		current_list = t_philo_sequential_current(info->sequential);
		if (!current_list)
			break ;
		if (current_list->data->status == PHILO_STATUS_DIE)
		{
			__philo_die_process(info, current_list->data);
			res = PHILO_SUCCESS;
		}
		else if (current_list->data->status == PHILO_STATUS_THINK)
			res = __philo_think_process(info, current_list->data);
		else
			continue ;
		if (res != PHILO_SUCCESS)
		{
			if (!t_philo_sequential_next(info->sequential))
			{
				t_philo_sequential_move_current_to_begin(info->sequential);
			}
		}
	}
	return (PHILO_SUCCESS);
}
