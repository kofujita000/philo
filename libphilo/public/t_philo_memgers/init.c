/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:27:53 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/07 23:21:10 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_members	*t_philo_members_init(
					const size_t size,
					pthread_mutex_t *const master_mtx)
{
	t_philo_members	*ret;
	size_t			pnt;

	ret = (t_philo_members *)malloc(sizeof(t_philo_members));
	if (!ret)
		return (ret);
	ret->data = NULL;
	ret->size = size;
	ret->data = (t_philo_member *)malloc(sizeof(t_philo_member) * size);
	if (!ret->data)
		return (t_philo_members_free(ret), ret = NULL, ret);
	pnt = size;
	while (pnt--)
		t_philo_member_init(&ret->data[pnt], pnt, master_mtx);
	return (ret);
}
