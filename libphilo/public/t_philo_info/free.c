/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:13:42 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/17 11:16:51 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_info_free(
			t_philo_info *const thiz)
{
	if (!thiz)
		return ;
	pthread_mutex_destroy(&thiz->mtx);
	(void)(thiz->members && (t_philo_members_free(thiz->members), 0));
	(void)(thiz->sequential && (t_philo_sequential_free(thiz->sequential), 0));
	free(thiz);
}
