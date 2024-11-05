/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moco <kofujita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:52:20 by moco              #+#    #+#             */
/*   Updated: 2024/11/06 00:52:37 by kofujita         ###   ########.fr       */
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
 * 1. uint32_t       my_number   -> 哲学者の個人番号
 * 2. uint32_t       wait_time   -> 待機時間
 * 3. t_philo_status status      -> ステータス
 * 4. uint8_t        fork_status -> フォークを持っているかどうか
 *  => (0 => フォークなし / 1 => フォークあり)
 *
 *****************************************************************************/
typedef struct s_philo_member
{
	uint32_t		my_number;
	uint32_t		wait_time;
	t_philo_status	status;
	uint8_t			fork;

}	t_philo_member;

/**
 * 哲学者個人の状態を引数で設定するための関数
 *
 * 1. t_philo_member *const -> 情報を代入するための構造体
 * 2. const uint32_t        -> 哲学者の個人番号
 * 3. const uint32_t        -> 待機時間 
 * 4. const t_philo_status  -> ステータス
 */
void			t_philo_member_set(
					t_philo_member *const thiz,
					const uint32_t my_number,
					const uint32_t wait_time,
					const t_philo_status status);

/******************************************************************************
 * 
 * 哲学者全体の状態
 * 1. t_philo_member *data -> メンバの配列情報
 * 2. size_t         size  -> メンバの数 
 *
 *****************************************************************************/
typedef struct s_philo_members
{
	t_philo_member	*data;
	size_t			size;

}	t_philo_members;

/**
 * 哲学者全体の構造体の初期化を行うための関数
 *
 * 1. const size_t -> メンバの数
 *
 * r. t_philo_members -> [!NULL => 初期化成功]
 *                       [NULL  => 初期化失敗]
 */
t_philo_members	*t_philo_members_init(
					const size_t size);

/**
 * 哲学者全体の構造体の解放を行うための関数
 *
 * 1. t_philo_members *const -> 解放したい構造体
 */
void			t_philo_members_free(
					t_philo_members *const thiz);

/******************************************************************************
 * 
 * プロジェクト全体のメンバ構造体
 * 1. プログラムを実行した際の引数情報
 * 2. 哲学者情報
 *
 *****************************************************************************/
typedef struct s_philo_info
{
	t_philo_params	parms;
	t_philo_members	*members;

}	t_philo_info;

#endif // PHILO_H
