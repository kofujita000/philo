/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:02:15 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/15 20:13:19 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_info	*t_philo_info_init(
					const int argc,
					const char **const argv)
{
	t_philo_info	*ret;
	t_philo_code	res;
	struct timeval	tv;

	ret = (t_philo_info *)malloc(sizeof(t_philo_info));
	if (!ret)
		return (ret);
	ret->members = NULL;
	ret->sequential = NULL;
	res = gettimeofday(&tv, NULL);
	if (res)
		return (t_philo_info_free(ret), NULL);
	ret->start_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	res = t_philo_params_init(&ret->parms, argc, argv);
	if (res != PHILO_SUCCESS)
		return (t_philo_info_free(ret), NULL);
	if (pthread_mutex_init(&ret->mtx, 0))
		return (t_philo_info_free(ret), NULL);
	ret->members = t_philo_members_init(ret->parms.count, ret);
	if (!ret->members)
		return (t_philo_info_free(ret), NULL);
	ret->sequential = t_philo_sequential_init(ret->members);
	if (!ret->sequential)
		return (t_philo_info_free(ret), NULL);
	return (ret);
}
