/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:32:27 by tlam              #+#    #+#             */
/*   Updated: 2024/03/20 11:32:28 by tlam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philosophers(t_data *data, t_philo *philo)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	if (pthread_create(&monitor, NULL, &monitoring, philo) != 0)
		error_msg_clean_exit("Error creating monitor thread\n", data);
	while (i < data->nbr_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
			error_msg_clean_exit("Error creating philo thread\n", data);
		i++;
	}
	i = 0;
	if (pthread_join(monitor, NULL) != 0)
		error_msg_clean_exit("Error joining monitor thread\n", data);
	while (i < data->nbr_philo)
	{
		if (pthread_join(philo[i].thread, NULL) != 0)
			error_msg_clean_exit("Error joining philo thread\n", data);
		i++;
	}
}

int	philo_is_not_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (philo->is_dead == 0)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (0);
	}
}

int	philo_did_not_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->is_eating_lock);
	if (philo->all_ate == 0)
	{
		pthread_mutex_unlock(philo->is_eating_lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->is_eating_lock);
		return (0);
	}
}

void	*routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->nbr_philo % 2 != 0 && philo->nbr_philo != 1)
	{
		if (philo->id == 1)
			ft_usleep(philo->time_to_eat * 2, philo);
	}
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_to_eat, philo);
	while (philo_is_not_dead(philo) && philo_did_not_eat(philo))
	{
		eating(philo);
		if (philo_is_not_dead(philo) && philo_did_not_eat(philo))
			sleeping(philo);
		if (philo_is_not_dead(philo) && philo_did_not_eat(philo))
			thinking(philo);
	}
	return (pointer);
}
