/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:34:08 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/17 10:46:11 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const t_philo_list	*t_philo_sequential_next(
						t_philo_sequential *const thiz)
{
	if (!thiz->current->next)
		return (NULL);
	thiz->before = thiz->current;
	thiz->current = thiz->current->next;
	return (thiz->current);
}
