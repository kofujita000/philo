/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:24:59 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/31 03:32:49 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_member_free(
			t_philo_member *const thiz)
{
	pthread_mutex_unlock(&thiz->mtx);
	pthread_join(thiz->ptid, NULL);
	pthread_mutex_destroy(&thiz->mtx);
}
