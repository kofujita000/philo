/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:46:43 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/07 23:19:46 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_code	t_philo_member_init(
					t_philo_member *const thiz,
					const int32_t my_number,
					pthread_mutex_t *const master_mtx)
{
	int	res;

	thiz->my_number = my_number;
	thiz->wait_time = 0;
	thiz->status = PHILO_STATUS_THINK;
	thiz->fork = PHILO_FORK_TRUE;
	thiz->member = NULL;
	thiz->ptid = 0;
	thiz->lock = PHILO_LOCK_FALSE;
	thiz->master_mtx = master_mtx;
	res = pthread_mutex_init(&thiz->mtx, 0);
	if (res)
		return (PHILO_ERROR_MEMBER_MUTEX_INIT);
	res = pthread_mutex_lock(&thiz->mtx);
	if (res)
		return (PHILO_ERROR_MEMBER_MUTEX_LOCK);
	res = pthread_create(&thiz->ptid, NULL, \
			(void *(*)(void *))__philo_thread_process, thiz);
	if (res)
		return (PHILO_ERROR_MEMBER_PTHREAD_CREATE);
	return (PHILO_SUCCESS);
}
