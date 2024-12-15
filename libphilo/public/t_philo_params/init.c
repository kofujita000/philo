/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 20:13:42 by kofujita          #+#    #+#             */
/*   Updated: 2024/12/15 17:52:20 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * パラメータの時間計をすべて 1000 かける
 *
 * 1. t_philo_params *const -> 情報を保持する構造体
 *
 * r. t_philo_code -> [PHILO_SUCCESS]
 *                    [...]
 */
static int	process1_times_1000(
				t_philo_params *const thiz);

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
	return (process1_times_1000(thiz));
}

int	process1_times_1000(
		t_philo_params *const thiz)
{
	if ((long long)((long long)thiz->eat * 1000) > INT_MAX)
		return (PHILO_ERROR_PARAM_PHILO_EAT);
	thiz->eat *= 1000;
	if ((long long)((long long)thiz->sleep * 1000) > INT_MAX)
		return (PHILO_ERROR_PARAM_PHILO_SLEEP);
	thiz->sleep *= 1000;
	return (PHILO_SUCCESS);
}
