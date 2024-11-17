/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:40:05 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/17 10:40:27 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const t_philo_list	*t_philo_sequential_current(
						t_philo_sequential *const thiz)
{
	return (thiz->current);
}
