/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kofujita <kofujita@student42.tokyo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:28:16 by kofujita          #+#    #+#             */
/*   Updated: 2024/11/17 11:21:21 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_info	*info;
	t_philo_code	res;

	info = t_philo_info_init(argc, (const char **const)argv);
	if (!info)
		return (PHILO_ERROR_INIT_INFO);
	res = philo_run(info);
	return (t_philo_info_free(info), res);
}
