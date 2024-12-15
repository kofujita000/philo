/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moco <kofujita@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 13:52:20 by moco              #+#    #+#             */
/*   Updated: 2024/12/15 20:44:10 by kofujita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_std/ft_std.h"

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <pthread.h>
# include <stdint.h>
# include <sys/time.h>

# define PHILO_MSG_TAKEN_FORK "%ld %d has taken a fork\n"
# define PHILO_MSG_EATING "%ld %d is eating\n"
# define PHILO_MSG_SLEEPING "%ld %d is sleeping\n"
# define PHILO_MSG_THINKING "%ld %d is thinking\n"
# define PHILO_MSG_DIED "%ld %d died\n"

/******************************************************************************
 *
 * philo のステータスコード
 * 1. PHILO_SUCCESS                          -> 処理成功 (成功)
 * 2. PHILO_ERROR_PARAM_COUNT                -> プログラムで受け取る引数の数が異なる
 * 3. PHILO_ERROR_PARAM_PHILO_COUNT          -> 哲学者の数が無効である
 * 4. PHILO_ERROR_PARAM_PHILO_DIE            -> 哲学者が亡くなる時間が無効である
 * 5. PHILO_ERROR_PARAM_PHILO_EAT            -> 哲学者が食べる時間が無効である
 * 6. PHILO_ERROR_PARAM_PHILO_SLEEP          -> 哲学者が眠る時間が無効である
 * 7. PHILO_ERROR_PARAM_PHILO_MUST_EAT_COUNT -> 哲学者の最大食事回数が無効である
 * 8. PHILO_ERROR_MEMTER_MUTEX_INIT          -> ミューテックスの初期化に失敗
 * 9. PHILO_ERROR_MEMBER_MUTEX_LOCK          -> ミューテックスのロックに失敗
 * 10. PHILO_ERROR_MEMBER_PTHREAD_CREATE     -> スレッドの作成に失敗
 * 11. PHILO_ERROR_INIT_INFO                 -> t_philo_info の初期化に失敗
 * 12. PHILO_USED_FORK                       -> フォーク使用中
 * 13. PHILO_ERROR_GET_TIME                  -> 現在時刻の取得に失敗
 * 14. PHILO_NONE_SIDE                       -> 隣がいない場合
 * 15. PHILO_ERROR_START_DIE_OVSERVER        -> 死亡監視の立ち上げに失敗
 * 16. PHILO_PASS                            -> 処理を通すためのもの
 *
 *****************************************************************************/
typedef enum s_philo_code
{
	PHILO_SUCCESS = 0,
	PHILO_ERROR_PARAM_COUNT,
	PHILO_ERROR_PARAM_PHILO_COUNT,
	PHILO_ERROR_PARAM_PHILO_DIE,
	PHILO_ERROR_PARAM_PHILO_EAT,
	PHILO_ERROR_PARAM_PHILO_SLEEP,
	PHILO_ERROR_PARAM_PHILO_MUST_EAT_COUNT,
	PHILO_ERROR_MEMBER_MUTEX_INIT,
	PHILO_ERROR_MEMBER_MUTEX_LOCK,
	PHILO_ERROR_MEMBER_PTHREAD_CREATE,
	PHILO_ERROR_INIT_INFO,
	PHILO_USED_FORK,
	PHILO_ERROR_GET_TIME,
	PHILO_NONE_SIDE,
	PHILO_ERROR_START_DIE_OVSERVER,
	PHILO_PASS,

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
 * フォークのステータス情報
 * 1. PHILO_FORK_TRUE  -> フォークが存在する
 * 2. PHILO_FORK_FALSE -> フォークが存在しない
 *
 *****************************************************************************/
typedef enum s_philo_fork
{
	PHILO_FORK_TRUE,
	PHILO_FORK_FALSE

}	t_philo_fork;

/******************************************************************************
 *
 * メンバ情報が現在処理中であるかどうかのフラグ
 * 1. PHILO_LOCK_TRUE  -> 処理中 (触れては行けない)
 * 2. PHILO_LOCK_FALSE -> 未処理 (触れて良い)
 *
 *****************************************************************************/
typedef enum s_philo_lock
{
	PHILO_LOCK_TRUE,
	PHILO_LOCK_FALSE,

}	t_philo_lock;

/******************************************************************************
 *
 * 哲学者の引数情報を保持する構造体
 * 1. int32_t count          -> 哲学者の数 (1~)
 * 2. int32_t die            -> 哲学者がお亡くなりになる時間 (millisecond)
 * 3. int32_t eat            -> 哲学者が食べる時間 (millisecond)
 * 4. int32_t sleep          -> 哲学者がお休みの時間 (millisecond)
 * 5. int32_t must_eat_count -> 哲学者の最大食事数 (~0の場合は無効)
 *  => 初期値: ~0
 *
 *****************************************************************************/
typedef struct s_philo_params
{
	int32_t		count;
	int32_t		die;
	int32_t		eat;
	int32_t		sleep;
	int32_t		must_eat_count;

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
t_philo_code			t_philo_params_init(
							t_philo_params *const thiz,
							const int argc,
							const char **argv);

/******************************************************************************
 * 
 * 哲学者個人の状態
 * 1. int32_t                my_number   -> 哲学者の個人番号
 * 2. struct timeval         wait_time   -> 食事開始時間
 * 3. struct timezone        timezone    -> タイムゾーン
 * 4. t_philo_status         status      -> ステータス
 * 5. t_philo_fork           fork_status -> フォークを持っているかどうか
 *  => (0 => フォークなし / 1 => フォークあり)
 * 6. pthread_t              ptid        -> スレッドID
 * 7. pthread_mutex_t        mtx         -> ミューテックス
 * 8. t_philo_params         *member     -> フォークを貸してもらうメンバ情報
 * 9. t_philo_lock           lock        -> 情報をロックしているかしていないか
 * 10. pthread_mutex_t        *master_mtx -> マスタのミューテックスアドレス
 * 11. const t_philo_params  *params     -> パラメータ情報のアドレス
 * 12. long                  start_time  -> 実行開始時間
 *
 *****************************************************************************/
typedef struct s_philo_member
{
	int32_t					my_number;
	struct timeval			eat_time;
	struct timezone			timezone;
	t_philo_status			status;
	t_philo_fork			fork;
	pthread_t				ptid;
	pthread_mutex_t			mtx;
	struct s_philo_member	*member;
	t_philo_lock			lock;
	pthread_mutex_t			*master_mtx;
	const t_philo_params	*params;
	long					start_time;

}	t_philo_member;

/**
 * 哲学者個人の状態初期化をするための関数
 *
 * 1. t_philo_member *const -> 情報を代入するための構造体
 * 2. const int32_t         -> 哲学者の個人番号
 * 3. void *const           -> t_philo_info のポインタ
 *
 * r. t_philo_code -> [PHILO_SUCCESS => 処理成功]
 *                    [...]
 */
t_philo_code			t_philo_member_init(
							t_philo_member *const thiz,
							const int32_t my_number,
							void *const info);

/**
 * 哲学の解放するための関数 (メモリを解放するわけではない)
 *
 * 1. t_philo_member *const -> 解放したい構造体
 */
void					t_philo_member_free(
							t_philo_member *const thiz);

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
 * 1. const size_t      -> メンバの数
 * 2. const void *const -> 情報を保持する構造体のアドレス
 *
 * r. t_philo_members -> [!NULL => 初期化成功]
 *                       [NULL  => 初期化失敗]
 */
t_philo_members			*t_philo_members_init(
							const size_t size,
							void *const info);

/**
 * 哲学者全体の構造体の解放を行うための関数
 *
 * 1. t_philo_members *const -> 解放したい構造体
 */
void					t_philo_members_free(
							t_philo_members *const thiz);

/******************************************************************************
 * 
 * 哲学者の順番リスト情報
 * 1. t_philo_member      *data -> メンバ情報のアドレス
 * 2. struct s_philo_list *next -> 次のリストアドレス
 *
 *****************************************************************************/
typedef struct s_philo_list
{
	t_philo_member		*data;
	struct s_philo_list	*next;

}	t_philo_list;

/******************************************************************************
 * 
 * 哲学者の順番情報
 * 1. t_philo_list *begin   -> 先頭のリストアドレス
 * 2. t_philo_list *end     -> 末尾のリストアドレス
 * 3. t_philo_list *before  -> current の前のリストアドレス
 * 4. t_philo_list *current -> 探索対象リストアドレス
 *
 *****************************************************************************/
typedef struct s_philo_sequential
{
	t_philo_list	*begin;
	t_philo_list	*end;
	t_philo_list	*before;
	t_philo_list	*current;

}	t_philo_sequential;

/**
 * 哲学者の順番情報を初期化するための関数
 *
 * 1. const t_philo_members *const -> 代入したい情報
 *
 * r. t_philo_sequential * -> [!NULL => 処理成功]
 *                            [NULL  => 処理失敗]
 */
t_philo_sequential		*t_philo_sequential_init(
							const t_philo_members *const members);

/**
 * 哲学者の順番情報を解放するための関数
 *
 * 1. t_philo_sequential *const -> 解放対象アドレス
 */
void					t_philo_sequential_free(
							t_philo_sequential *const thiz);

/**
 * 順番情報のカレントを取得するための関数
 *
 * 1. t_philo_sequential *const -> 情報を保持する構造体
 *
 * r. const t_philo_list * -> カレントリスト情報
 */
const t_philo_list		*t_philo_sequential_current(
							t_philo_sequential *const thiz);

/**
 * 順番情報を一つ先に進めるための関数
 *
 * 1. t_philo_sequential *const -> 情報を保持する構造体
 *
 * r. const t_philo_list * -> 移動後リスト情報
 *  > (NULL の場合は末尾にいることを表す)
 */
const t_philo_list		*t_philo_sequential_next(
							t_philo_sequential *const thiz);

/**
 * カレント情報を末尾に移動させるための関数 (カレントが先頭に戻る)
 *
 * 1. t_philo_sequential *const -> 情報を保持する構造体
 */
void					t_philo_sequential_move_end(
							t_philo_sequential *const thiz);

/**
 * カレント情報を削除するための関数 (カレントが次のアドレスに移動する)
 *  > リストメモリも解放
 *
 * 1. t_philo_sequential *const -> 情報を保持する構造体
 */
void					t_philo_sequential_erase(
							t_philo_sequential *const thiz);

/**
 * カレント情報を先頭に移動させるための関数
 *
 * 1. t_philo_sequential *const -> 情報を保持する構造体
 */
void					t_philo_sequential_move_current_to_begin(
							t_philo_sequential *const thiz);

/**
 * カレントが末尾かどうかを確かめるための関数
 *
 * 1. t_philo_sequential *const -> 情報を保持する構造体
 *
 * r. int -> [0 => 末尾ではない]
 *           [1 => 末尾である]
 */
int						t_philo_sequential_is_end(
							t_philo_sequential *const thiz);

/******************************************************************************
 * 
 * プロジェクト全体のメンバ構造体
 * 1. プログラムを実行した際の引数情報
 * 2. 哲学者情報
 * 3. 哲学者の順番情報
 * 4. 占有ロック制御のためのミューテックス
 * 5. 共有ロック制御のためのフラグ
 * 6. 死者の観測を行うためのスレッド (死者にクチナシ)
 * 7. 死者観測を制御するフラグ (1 => 稼働 / 0 => 終了)
 * 8. 開始時のタイムスタンプ
 *
 *****************************************************************************/
typedef struct s_philo_info
{
	t_philo_params		parms;
	t_philo_members		*members;
	t_philo_sequential	*sequential;
	pthread_mutex_t		mtx;
	pthread_t			die_ovserver_ptid;
	int					die_ovserver_flag;
	long				start_time;

}	t_philo_info;

/**
 * プロジェクト全体の構造体を初期化するための関数
 *
 * 1. const int         -> プログラム実行時の引数の数
 * 2. const char *const -> プログラム実行時の引数情報
 */
t_philo_info			*t_philo_info_init(
							const int argc,
							const char **const argv);

/**
 * プロジェクト全体の構造体を解放するための関数
 *
 * 1. t_philo_info *const -> 解放対象構造体
 */
void					t_philo_info_free(
							t_philo_info *const thiz);

/* ========================================================================== */

/**
 * プログラムの処理を開始するための関数
 *
 * 1. t_philo_info *const -> 情報を保持する構造体
 *
 * r. t_philo_code -> [PHILO_SUCCESS => 処理成功]
 *                    [...]
 */
t_philo_code			philo_run(
							t_philo_info *const info);

/**
 * スレッドが実行する関数
 *
 * 1. t_philo_member *const -> スレッドに渡したい情報を保持する構造体
 */
void					*__philo_thread_process(
							t_philo_member *const member);

/**
 * 死者を監視するための関数
 *
 * 1. t_philo_info *const -> 情報を保持する構造体
 *
 * r. t_philo_code -> [PHILO_SUCCESS => 処理成功]
 *                    [...]
 */
t_philo_code			__philo_run_die_ovserver(
							t_philo_info *const info);

/**
 * 哲学者に対して命令を出すための関数
 *
 * 1. t_philo_info *const -> 情報を保持する構造体
 *
 * r. t_philo_code -> [PHILO_SUCCESS => 処理成功]
 *                    [...]
 */
t_philo_code			__philo_run_commander(
							t_philo_info *const info);

/**
 * 哲学者が死亡していた場合の処理関数 (カレント情報が対象)
 *
 * 1. t_philo_info *const -> 情報を保持する構造体
 *
 * r. t_philo_code -> [PHILO_SUCCESS => 処理成功]
 *                    [...]
 */
void					__philo_die_process(
							t_philo_info *const info,
							t_philo_member *const member);

/**
 * 哲学者が考えている場合の処理関数 (カレント情報が対象)
 *
 * 1. t_philo_info *const 
 */
t_philo_code			__philo_think_process(
							t_philo_info *const info,
							t_philo_member *const member);

/**
 * 哲学者がフォークを取った時間を出力するための関数
 *
 * 1. const int32_t -> 実行開始タイムスタンプ
 * 2. const int32_t -> 哲学者番号
 */
void					__philo_print_taken_fork(
							const long start_time,
							const int32_t my_number);

/**
 * 哲学者が食べ始めた時間を出力するための関数
 *
 * 1. const int32_t -> 実行開始タイムスタンプ
 * 2. const int32_t -> 哲学者番号
 */
void					__philo_print_eating(
							const long start_time,
							const int32_t my_number);

/**
 * 哲学者が眠り始めた時間を出力するための関数
 *
 * 1. const int32_t -> 実行開始タイムスタンプ
 * 2. const int32_t -> 哲学者番号
 */
void					__philo_print_sleeping(
							const long start_time,
							const int32_t my_number);

/**
 * 哲学者が考え始めた時間を出力するための関数
 *
 * 1. const int32_t -> 実行開始タイムスタンプ
 * 2. const int32_t -> 哲学者番号
 */
void					__philo_print_thinking(
							const long start_time,
							const int32_t my_number);

/**
 * 哲学者がお亡くなりになった時間を出力するための関数
 *
 * 1. const int32_t -> 実行開始タイムスタンプ
 * 2. const int32_t -> 哲学者番号
 */
void					__philo_print_died(
							const long start_time,
							const int32_t my_number);

#endif // PHILO_H
