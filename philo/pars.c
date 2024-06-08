/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achater <achater@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:32:52 by achater           #+#    #+#             */
/*   Updated: 2024/06/07 15:08:23 by achater          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	long	nb;

	i = 0;
	nb = 0;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		nb = nb * 10 + str[i] - '0';
		if (nb > 2147483647)
			return (-1);
		i++;
	}
	return (nb);
}

int check_arg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_arg(char *str)
{
	int	i;

	if(check_arg(str) == 0)
	{
		printf("Error: Invalid argument\n");
		return (-1);
	}
	i = ft_atoi(str);
	return (i);
}
