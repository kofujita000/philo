/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:33:53 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/07 23:24:42 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	t_philo_members_free(
			t_philo_members *const thiz)
{
	size_t	pnt;

	if (thiz)
	{
		if (thiz->data)
		{
			pnt = thiz->size;
			while (pnt--)
				t_philo_member_free(&thiz->data[pnt]);
			ft_std_memset(thiz->data, 0, sizeof(*thiz->data) * thiz->size);
			free(thiz->data);
		}
		ft_std_memset(thiz, 0, sizeof(*thiz));
		free(thiz);
	}
}
