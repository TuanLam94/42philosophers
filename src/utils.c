/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:19:04 by tlam              #+#    #+#             */
/*   Updated: 2024/03/22 17:19:05 by tlam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_philo_state(char *str, t_philo *philo)
{
	int	time;

	pthread_mutex_lock(philo->print_lock);
	time = get_current_time() - philo->start;
	if (!philo_is_not_dead(philo))
	{
		pthread_mutex_unlock(philo->print_lock);
		return ;
	}
	printf("%d philosopher %d %s", time, philo->id, str);
	pthread_mutex_unlock(philo->print_lock);
}

int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

void	ft_usleep(int nb, t_philo *philo)
{
	struct timeval	start;
	struct timeval	current;
	long			elapsed_time;

	if (nb <= 0)
		return ;
	elapsed_time = 0;
	gettimeofday(&start, NULL);
	while (elapsed_time < nb)
	{
		gettimeofday(&current, NULL);
		elapsed_time = (current.tv_sec - start.tv_sec) * 1000
			+ (current.tv_usec - start.tv_usec) / 1000;
		if (!philo_is_not_dead(philo) || !philo_did_not_eat(philo))
			return ;
		usleep(50);
	}
}
