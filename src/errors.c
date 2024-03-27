/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:29:01 by tlam              #+#    #+#             */
/*   Updated: 2024/03/19 15:29:02 by tlam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error_msg(char *str)
{
	write(2, str, ft_strlen(str));
	exit(1);
}

void	error_msg_clean_exit(char *str, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->forks[i++]);
		pthread_mutex_destroy(&data->is_eating_lock[i]);
		i++;
	}
	write(2, str, ft_strlen(str));
	exit(1);
}

void	end_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->is_eating_lock[i]);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
}
