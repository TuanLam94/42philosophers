/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:26:52 by tlam              #+#    #+#             */
/*   Updated: 2024/03/19 14:26:54 by tlam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **argv)
{
	if (!is_numeric(argv[1]) || ft_atoi(argv[1]) > PHILO_MAX
		|| ft_atoi(argv[1]) <= 0)
		return (error_msg("Invalid philosophers number\n"), 0);
	if (!is_numeric(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (error_msg("Invalid time to die\n"), 0);
	if (!is_numeric(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (error_msg("Invalid time to eat\n"), 0);
	if (!is_numeric(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (error_msg("Invalid time to sleep\n"), 0);
	if (argv[5] && ((!is_numeric(argv[5])) || (ft_atoi(argv[5])) < 0))
		return (error_msg("Invalid number of times each philo must eat\n"), 0);
	return (1);
}

void	init_philo(t_data *data, t_philo *philo, char **argv)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].id = i + 1;
		philo[i].last_meal = get_current_time();
		philo[i].meals_eaten = 0;
		philo[i].meals_to_eat = data->meals_to_eat;
		philo[i].nbr_philo = ft_atoi(argv[1]);
		philo[i].time_to_die = ft_atoi(argv[2]);
		philo[i].time_to_eat = ft_atoi(argv[3]);
		philo[i].time_to_sleep = ft_atoi(argv[4]);
		philo[i].start = data->start;
		philo[i].is_dead = 0;
		philo[i].all_ate = 0;
		philo[i].print_lock = &data->print_lock;
		philo[i].dead_lock = &data->dead_lock;
		philo[i].is_eating_lock = &data->is_eating_lock[i];
		i++;
	}
}

void	init_forks(t_data *data, pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < data->nbr_philo)
	{
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[data->nbr_philo - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}

void	init(t_data *data, t_philo *philo, pthread_mutex_t *forks, char **argv)
{
	int				i;

	i = 0;
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	while (i < ft_atoi(argv[1]))
		pthread_mutex_init(&data->is_eating_lock[i++], NULL);
	data->philo = philo;
	data->forks = forks;
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_to_eat = ft_atoi(argv[5]);
	else
		data->meals_to_eat = -1;
	data->start = get_current_time();
	init_forks(data, forks, philo);
	init_philo(data, philo, argv);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (argc < 5 || argc > 6)
		error_msg("Wrong number of arguments\n");
	check_args(argv);
	init(&data, philo, forks, argv);
	philosophers(&data, philo);
	end_philo(&data);
	return (0);
}
