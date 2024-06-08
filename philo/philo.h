/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:12:00 by achater           #+#    #+#             */
/*   Updated: 2024/06/08 12:12:19 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philosopher {
    int id;
    int flag;
    int times_eaten;
    long long last_meal_time;
    pthread_t thread;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    struct s_data *data;
} t_philosopher;

typedef struct s_data {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int meals_needed;
    int all_ate;
    pthread_mutex_t time_lock;
    pthread_mutex_t meals_lock;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    long long start_time;
    t_philosopher *philosophers;
} t_data;

int	parse_arg(char *str);
long long	current_time_ms(void);
void	*philosopher_routine(t_philosopher *philosopher);
void    monitor_routine(t_data *data);
void    mutex_destroy(t_data *data);


# endif