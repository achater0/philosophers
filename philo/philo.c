/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:12:10 by achater           #+#    #+#             */
/*   Updated: 2024/06/06 15:13:52 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

void	init_data(t_data *data, char	**av, int 	ac)
{
	data->num_philosophers = parse_arg(av[1]);
	data->time_to_die = parse_arg(av[2]);
	data->time_to_eat = parse_arg(av[3]);
	data->time_to_sleep = parse_arg(av[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60)
	{
		printf("Error: Arguments too low\n");
		exit(1);
	}
	if (ac == 6)
		data->meals_needed = parse_arg(av[5]);
	else
		data->meals_needed = -1;
	data->all_ate = 0;
	data->start_time = current_time_ms();
	pthread_mutex_init(&data->print_lock, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (data->forks == NULL)
	{
		printf("Error: Malloc failed\n");
		exit(1);
	}
	i = 0;
	while (i < data->num_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}
void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philosophers = malloc(sizeof(t_philosopher) * data->num_philosophers);
	if (data->philosophers == NULL)
	{
		printf("Error: Malloc failed\n");
		exit(1);
	}
	while(i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].times_eaten = 0;
		data->philosophers[i].last_meal_time = data->start_time;
		data->philosophers[i].data = data;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		pthread_create(&data->philosophers[i].thread, NULL, (void *(*)(void *))philosopher_routine, &data->philosophers[i]);
		i++;
	}
	// init_monitor(data);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	init_data(&data, av, ac);
	init_forks(&data);
	init_philosophers(&data);
	monitor_routine(&data);
	while (i < data.num_philosophers)
	{
		pthread_join(data.philosophers[i].thread, NULL);
		i++;
	}
	free(data.philosophers);
	free(data.forks);
	return (0);
}
