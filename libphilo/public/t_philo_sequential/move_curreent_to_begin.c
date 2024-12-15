/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_curreent_to_begin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:34:08 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/15 21:49:06 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_sequential_move_current_to_begin(
			t_philo_sequential *const thiz)
{
	thiz->current = thiz->begin;
	thiz->before = NULL;
}
