/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moco <kofujita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:52:20 by moco              #+#    #+#             */
/*   Updated: 2024/11/02 15:07:39 by moco             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>

/******************************************************************************
 *
 * philo のステータスコード
 * 1. PHILO_SUCCESS                     -> 処理成功 (成功)
 * 2. PHILO_ERROR_PARAM_COUNT           -> プログラムで受け取る引数の数が異なる
 * 3. PHILO_ERROR_PARAM_CONVERT_NUMERIC -> プログラムで受け取る引数の数値変換失敗
 * 4. PHILO_ERROR_PARAM_PHILO_COUNT     -> 哲学者の数が無効な数字である
 *
 *****************************************************************************/
typedef enum s_philo_code
{
	PHILO_SUCCESS = 0,
	PHILO_ERROR_PARAM_COUNT,
	PHILO_ERROR_PARAM_CONVERT_NUMERIC,
	PHILO_ERROR_PARAM_PHILO_COUNT

}	t_philo_code;

/******************************************************************************
 *
 * philo のステータス
 * 1. PHILO_STATUS_EAT   -> 食事ステータス
 * 2. PHILO_STATUS_SLEEP -> 寝るステータス
 * 3. PHILO_STATUS_THINK -> 考えるステータス
 * 4. PHILO_STATUS_DIE   -> 死亡ステータス
 *
 *****************************************************************************/
typedef enum s_philo_status
{
	PHILO_STATUS_EAT = 0,
	PHILO_STATUS_SLEEP,
	PHILO_STATUS_THINK,
	PHILO_STATUS_DIE,

}	t_philo_status;

/******************************************************************************
 *
 * 哲学者の引数情報を保持する構造体
 * 1. uint32_t count          -> 哲学者の数 (1~)
 * 2. uint32_t die            -> 哲学者がお亡くなりになる時間 (millisecond)
 * 3. uint32_t eat            -> 哲学者が食べる時間 (millisecond)
 * 4. uint32_t sleep          -> 哲学者がお休みの時間 (millisecond)
 * 5. uint32_t must_eat_count -> 哲学者の最大食事数 (~0の場合は無効)
 *  => 初期値: ~0
 *
 *****************************************************************************/
typedef struct s_philo_params
{
	uint32_t	count;
	uint32_t	die;
	uint32_t	eat;
	uint32_t	sleep;
	uint32_t	must_eat_count;

}	t_philo_params;

/**
 * t_philo_params の中身を初期化するための関数
 *
 * 1. t_philo_params *const -> 初期化したい構造体 (メモリは保持されているものとする)
 * 2. const int             -> プログラムの引数の数
 * 3. const char *const     -> プログラムの引数
 *
 * r. t_philo_code -> [PHILO_SUCCESS => 処理成功]
 *                    [PHILO_ERROR_PARAM_COUNT]
 *                    [PHILO_ERROR_PARAM_CONVERT_NUMERIC]
 */
t_philo_code	t_philo_params_init(
					t_philo_params *const thiz,
					const int argc,
					const char **argv);

/******************************************************************************
 * 
 * 哲学者個人の状態
 * 1. uint32_t       wait_time -> 待機時間
 * 2. t_philo_status status    -> ステータス
 *
 *****************************************************************************/
typedef struct s_philo_member
{
	uint32_t		wait_time;
	t_philo_status	status;

}	t_philo_status;

/******************************************************************************
 * 
 * プロジェクト全体のメンバ構造体
 *
 *****************************************************************************/
typedef struct s_philo_info
{
	t_philo_params	parms;

}	t_philo_info;

#endif // PHILO_H
