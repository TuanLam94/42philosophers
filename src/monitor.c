/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:45:54 by tlam              #+#    #+#             */
/*   Updated: 2024/03/19 15:45:56 by tlam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_is_dead(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nbr_philo)
	{
		pthread_mutex_lock(philo[i].is_eating_lock);
		if ((get_current_time() - philo[i].last_meal > philo[i].time_to_die))
		{
			if (philo[0].nbr_philo != 1)
				print_philo_state("died\n", &philo[i]);
			assign_to_all_philos(philo, 1);
			pthread_mutex_unlock(philo[i].is_eating_lock);
			return (1);
		}
		pthread_mutex_unlock(philo[i].is_eating_lock);
		i++;
	}
	return (0);
}

int	all_philo_ate(t_philo *philo)
{
	int	i;
	int	philo_ate;

	i = 0;
	philo_ate = 0;
	if (philo->meals_to_eat == -1)
		return (0);
	while (i < philo->nbr_philo)
	{
		pthread_mutex_lock(philo[i].is_eating_lock);
		if (philo[i].meals_eaten >= philo[i].meals_to_eat)
			philo_ate++;
		pthread_mutex_unlock(philo[i].is_eating_lock);
		i++;
	}
	if (philo_ate == philo->nbr_philo)
	{
		assign_to_all_philos(philo, 2);
		return (1);
	}
	else
		return (0);
}

void	assign_to_all_philos(t_philo *philo, int type)
{
	int	i;

	i = 0;
	if (type == 1)
	{
		while (i < philo->nbr_philo)
		{
			pthread_mutex_lock(philo[i].dead_lock);
			philo[i].is_dead = 1;
			pthread_mutex_unlock(philo[i].dead_lock);
			i++;
		}
	}
	if (type == 2)
	{
		while (i < philo->nbr_philo)
		{
			pthread_mutex_lock(philo[i].is_eating_lock);
			philo[i].all_ate = 1;
			pthread_mutex_unlock(philo[i].is_eating_lock);
			i++;
		}
	}
}

void	*monitoring(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	while (1)
	{
		if (philo_is_dead(philo))
			break ;
		if (all_philo_ate(philo))
			break ;
	}
	return (pointer);
}
