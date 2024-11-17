/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_end.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:59:26 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/17 11:00:03 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int						t_philo_sequential_is_end(
							t_philo_sequential *const thiz)
{
	return (thiz->current == thiz->end);
}
