/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:46:43 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 21:35:35 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	process1_init_value(
				t_philo_member *const thiz,
				const int32_t my_number,
				t_philo_info *const info,
				struct s_philo_members *members);

t_philo_code	t_philo_member_init(
					t_philo_member *const thiz,
					const int32_t my_number,
					void *const info,
					struct s_philo_members *members)
{
	int	res;

	process1_init_value(thiz, my_number, info, members);
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
	res = gettimeofday(&thiz->eat_time, &thiz->timezone);
	if (res)
		return (PHILO_ERROR_GET_TIME);
	return (PHILO_SUCCESS);
}

void	process1_init_value(
			t_philo_member *const thiz,
			const int32_t my_number,
			t_philo_info *const info,
			struct s_philo_members *members)
{
	thiz->my_number = my_number;
	thiz->status = PHILO_STATUS_THINK;
	thiz->fork = PHILO_FORK_TRUE;
	thiz->member = NULL;
	thiz->ptid = 0;
	thiz->exit_flag = &info->exit_flag;
	thiz->master_mtx = &info->mtx;
	thiz->params = &info->parms;
	thiz->start_time = info->start_time;
	thiz->eat_count = 0;
	thiz->members = members;
}
