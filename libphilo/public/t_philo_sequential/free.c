/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:26:39 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/17 10:29:19 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_sequential_free(
			t_philo_sequential *const thiz)
{
	t_philo_list	*next;
	t_philo_list	*buf;

	if (!thiz)
		return ;
	buf = thiz->begin;
	while (buf)
	{
		next = buf->next;
		free(buf);
		buf = next;
	}
	free(thiz);
}
