/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 12:12:10 by achater           #+#    #+#             */
/*   Updated: 2024/06/08 11:26:28 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	check(t_data *data)
{
	if (data->time_to_die < 60 || data->time_to_eat < 60 || data->time_to_sleep < 60 || data->num_philosophers < 1)
	{
		printf("invalid argument\n");
		return (0);
	}
	return (1);
}

void	init_data(t_data *data, char	**av, int 	ac)
{
	data->num_philosophers = parse_arg(av[1]);
	data->time_to_die = parse_arg(av[2]);
	data->time_to_eat = parse_arg(av[3]);
	data->time_to_sleep = parse_arg(av[4]);
	if (ac == 6)
	{
		data->meals_needed = parse_arg(av[5]);
		if (data->meals_needed == -1)
		{
			printf("Error: Invalid number of meals\n");
			return ;
		}
	}
	else
		data->meals_needed = -1;
	data->all_ate = 0;
	data->start_time = current_time_ms();
	data->dead = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->meals_lock, NULL);
	pthread_mutex_init(&data->time_lock, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philosophers);
	if (data->forks == NULL)
	{
		printf("Error: Malloc failed\n");
		return ;
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
		return ;
	}
	while(i < data->num_philosophers)
	{
		data->philosophers[i].id = i + 1;
		data->philosophers[i].times_eaten = 0;
		data->philosophers[i].last_meal_time = data->start_time;
		data->philosophers[i].data = data;
		data->philosophers[i].left_fork = &data->forks[i];
		data->philosophers[i].right_fork = &data->forks[(i + 1) % data->num_philosophers];
		data->philosophers[i].flag = 0;
		i++;
	}
	i = -1;
	while (++i < data->num_philosophers)
	{
		pthread_create(&data->philosophers[i].thread, NULL, (void *)philosopher_routine, &data->philosophers[i]);
	}
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
	if (data.meals_needed == 0 || check(&data) == 0)
		return (1);
	init_forks(&data);
	init_philosophers(&data);
	while (i < data.num_philosophers)
	{
		pthread_detach(data.philosophers[i].thread);
		i++;
	}
	monitor_routine(&data);
	mutex_destroy(&data);
	return (0);
}
