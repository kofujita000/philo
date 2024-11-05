# Philosophers

**利用関数**

- memset
- printf
- malloc
- free
- write
- usleep
- gettimeofday
- pthread_create
- pthread_detach
- pthread_join
- pthread_mutex_init,
- pthread_mutex_destroy
- pthread_mutex_lock,
- pthread_mutex_unlock

<br>

**コンパイル手順**

<br>

**Parameters**

```bash
# 哲学者の数
NUMBER_OF_PHILOSOPHERS=5

# 哲学者がお亡くなりになる時間 (millisecond)
TIME_TO_DIE=1000

# 哲学者が食べる時間 (millisecond)(2つのforkを使うらしい)
TIME_TO_EAT=1000

# 哲学者がお休みの時間 (millisecond)
TIME_TO_SLEEP=1000

# 哲学者の最大食事カウント数 (指定がない場合は誰かがお亡くなりになるまで続行)
NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT=10

philo \
    "$NUMBER_OF_PHILOSOPHERS" \
    "$TIME_TO_DIE" \
    "$TIME_TO_EAT" \
    "$TIME_TO_SLEEP" \
    "$NUMBER_OF_TIMES_EACH_PHILOSOPHER_MUST_EAT"
```


## サイクル

`ご飯食べる` => `寝て` => `考える(必要なし)` => `ご飯を食べる`
 
- 食べ始めると 死ぬ 時間が 0 に戻される
- 考える必要な特段なし

## 考えている人のキューを作成する必要があるかもしれない
