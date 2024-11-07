/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:13:42 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/07 20:13:46 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo_code	t_philo_params_init(
					t_philo_params *const thiz,
					const int argc,
					const char **argv)
{
	int		res;

	if (argc != 5 && argc != 6)
		return (PHILO_ERROR_PARAM_COUNT);
	res = ft_std_atoi(argv[1], NULL, &thiz->count);
	if (res || thiz->count < 1)
		return (PHILO_ERROR_PARAM_PHILO_COUNT);
	res = ft_std_atoi(argv[2], NULL, &thiz->die);
	if (res || thiz->die < 0)
		return (PHILO_ERROR_PARAM_PHILO_DIE);
	res = ft_std_atoi(argv[3], NULL, &thiz->eat);
	if (res || thiz->eat < 0)
		return (PHILO_ERROR_PARAM_PHILO_EAT);
	res = ft_std_atoi(argv[4], NULL, &thiz->sleep);
	if (res || thiz->sleep < 0)
		return (PHILO_ERROR_PARAM_PHILO_SLEEP);
	if (argc == 6)
	{
		res = ft_std_atoi(argv[5], NULL, &thiz->must_eat_count);
		if (res || thiz->must_eat_count < 0)
			return (PHILO_ERROR_PARAM_PHILO_MUST_EAT_COUNT);
	}
	return (PHILO_SUCCESS);
}
