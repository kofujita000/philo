/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commander.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 17:34:12 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/14 01:20:19 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_code	__philo_run_commander(
					t_philo_info *const info)
{
	t_philo_code		ret;
	const t_philo_list	*current_list;

	ret = PHILO_SUCCESS;
	while (1)
	{
		current_list = t_philo_sequential_current(info->sequential);
		if (!current_list)
			break ;
		if (current_list->data->status == PHILO_STATUS_DIE)
			__philo_die_process(info, current_list->data);
		else if (current_list->data->status == PHILO_STATUS_THINK)
			__philo_think_process(info, current_list->data);
		else
		{
			if (!t_philo_sequential_next(info->sequential))
				t_philo_sequential_move_current_to_begin(info->sequential);
		}
	}
	return (ret);
}
