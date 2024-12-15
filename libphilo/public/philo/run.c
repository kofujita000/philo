/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 11:23:37 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/15 17:51:11 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_code	philo_run(
					t_philo_info *const info)
{
	t_philo_code	ret;

	info->die_ovserver_flag = 1;
	ret = __philo_run_die_ovserver(info);
	if (ret != PHILO_SUCCESS)
		return (ret);
	ret = __philo_run_commander(info);
	return (ret);
}
