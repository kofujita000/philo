/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:13:42 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/14 01:17:14 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_info_free(
			t_philo_info *const thiz)
{
	if (!thiz)
		return ;
	thiz->die_ovserver_flag = 0;
	pthread_join(thiz->die_ovserver_ptid, NULL);
	pthread_mutex_destroy(&thiz->mtx);
	(void)(thiz->members && (t_philo_members_free(thiz->members), 0));
	(void)(thiz->sequential && (t_philo_sequential_free(thiz->sequential), 0));
	free(thiz);
}
