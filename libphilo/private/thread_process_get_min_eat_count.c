/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_process_get_min_eat_count.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 21:28:25 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 21:31:37 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int32_t	__philo_thread_process_get_min_eat_count(
			const t_philo_members *const members)
{
	int32_t	ret;
	size_t	cnt;

	ret = INT_MAX;
	cnt = 0;
	while (members->size != cnt)
	{
		if (members->data[cnt].eat_count < ret)
			ret = members->data[cnt].eat_count;
		cnt++;
	}
	return (ret);
}
