/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:40:46 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/14 01:05:32 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_sequential_erase(
			t_philo_sequential *const thiz)
{
	t_philo_list	*buf;

	if (thiz->current == thiz->end)
	{
		thiz->end = thiz->before;
		buf = thiz->current->next;
		if (thiz->before)
			thiz->before->next = buf;
		free(thiz->current);
		thiz->current = buf;
	}
	else
	{
		buf = thiz->current->next;
		if (thiz->before)
			thiz->before->next = buf;
		free(thiz->current);
		thiz->current = buf;
	}
}
