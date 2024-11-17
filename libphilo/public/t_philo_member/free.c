/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 23:24:59 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/07 23:26:35 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_member_free(
			t_philo_member *const thiz)
{
	pthread_mutex_destroy(&thiz->mtx);
	pthread_detach(thiz->ptid);
}
