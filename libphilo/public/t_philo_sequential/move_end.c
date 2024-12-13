/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:36:26 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/13 23:49:17 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_sequential_move_end(
			t_philo_sequential *const thiz)
{
	thiz->end->next = thiz->current;
	thiz->end = thiz->current;
	if (thiz->before)
		thiz->before->next = thiz->current->next;
	else
		thiz->begin = thiz->begin->next;
	t_philo_sequential_move_current_to_begin(thiz);
}
