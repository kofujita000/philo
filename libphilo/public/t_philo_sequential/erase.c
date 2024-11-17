/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   erase.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:40:46 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/17 10:55:17 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_sequential_erase(
			t_philo_sequential *const thiz)
{
	if (thiz->current == thiz->end)
	{
		thiz->end = thiz->before;
		thiz->before->next = thiz->current->next;
		free(thiz->current);
		thiz->current = thiz->before;
	}
	else
	{
		thiz->before->next = thiz->current->next;
		free(thiz->current);
		thiz->current = thiz->before->next;
	}
}
