/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:41:43 by achater           #+#    #+#             */
/*   Updated: 2024/06/06 14:37:18 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

long long	current_time_ms(void)
{
	struct timeval	time;
	long long		time_ms;

	gettimeofday(&time, NULL);
	time_ms = time.tv_sec * 1000;
	time_ms += time.tv_usec / 1000;
	return (time_ms);
}
long	my_usleep(long long time)
{
	long long	start;

	start = current_time_ms();
	while (current_time_ms() - start < time)
		usleep(100);
	return (0);
}
void ft_eat(int time, t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(&philosopher->data->print_lock);
	printf("%lld %d has taken a fork\n", current_time_ms() - philosopher->data->start_time, philosopher->id);
	pthread_mutex_unlock(&philosopher->data->print_lock);
	pthread_mutex_lock(philosopher->right_fork);
	pthread_mutex_lock(&philosopher->data->print_lock);
	printf("%lld %d has taken a fork\n", current_time_ms() - philosopher->data->start_time, philosopher->id);
	printf("%lld %d is eating\n", current_time_ms() - philosopher->data->start_time, philosopher->id);
	pthread_mutex_unlock(&philosopher->data->print_lock);
	philosopher->last_meal_time = current_time_ms();
	my_usleep(time);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	philosopher->times_eaten++;
}


void	*philosopher_routine(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		ft_eat(philosopher->data->time_to_eat, philosopher);
		pthread_mutex_lock(&philosopher->data->print_lock);
		printf("%lld %d is sleeping\n", current_time_ms() - philosopher->data->start_time, philosopher->id);
		pthread_mutex_unlock(&philosopher->data->print_lock);
		my_usleep(philosopher->data->time_to_sleep);
		pthread_mutex_lock(&philosopher->data->print_lock);
		printf("%lld %d is thinking\n", current_time_ms() - philosopher->data->start_time, philosopher->id);
		pthread_mutex_unlock(&philosopher->data->print_lock);
		// printf("im here\n");
		// sleep(1);
	}
}
void *monitor_routine(t_data *data)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->num_philosophers)
		{
			if (data->meals_needed != -1 && data->philosophers[i].times_eaten == data->meals_needed)
				data->all_ate++;
			if (data->all_ate == data->num_philosophers)
			{
				pthread_mutex_lock(&data->print_lock);
				printf("All philosophers have eaten %d times\n", data->meals_needed);
				pthread_mutex_unlock(&data->print_lock);
				exit(0);
			}
			if (current_time_ms() - data->philosophers[i].last_meal_time > data->time_to_die)
			{
				pthread_mutex_lock(&data->print_lock);
				printf("%lld %d died\n", current_time_ms() - data->start_time, data->philosophers[i].id);
				pthread_mutex_unlock(&data->print_lock);
				exit(0);
			}
			i++;
		}
		usleep(1000);
	}

}
