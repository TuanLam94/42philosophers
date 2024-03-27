/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:30:48 by tlam              #+#    #+#             */
/*   Updated: 2024/03/22 17:30:49 by tlam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eating(t_philo *philo)
{
	if (!philo_is_not_dead(philo) || !philo_did_not_eat(philo))
		return ;
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	print_philo_state("has taken a fork\n", philo);
	if (philo->nbr_philo == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		print_philo_state("died\n", philo);
		philo->is_dead = 1;
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	print_philo_state("has taken a fork\n", philo);
	eating2(philo);
}

void	eating2(t_philo *philo)
{
	pthread_mutex_lock(philo->is_eating_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	print_philo_state("is eating\n", philo);
	pthread_mutex_unlock(philo->is_eating_lock);
	ft_usleep(philo->time_to_eat, philo);
	if (philo->id % 2 == 0)
		pthread_mutex_unlock(philo->l_fork);
	else
		pthread_mutex_unlock(philo->r_fork);
	if (philo->id % 2 == 0)
		pthread_mutex_unlock(philo->r_fork);
	else
		pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	print_philo_state("is sleeping\n", philo);
	ft_usleep(philo->time_to_sleep, philo);
}

void	thinking(t_philo *philo)
{
	print_philo_state("is thinking\n", philo);
	if (philo->nbr_philo % 2 == 0)
		ft_usleep(philo->time_to_eat - philo->time_to_sleep, philo);
	else
		ft_usleep(philo->time_to_eat * 2 - philo->time_to_sleep, philo);
}
