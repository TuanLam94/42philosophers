/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlam <tlam@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:33:07 by tlam              #+#    #+#             */
/*   Updated: 2024/03/19 14:33:09 by tlam             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# ifndef PHILO_MAX
#  define PHILO_MAX 250
# endif

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <../libft/includes/libft.h>

typedef struct s_philo
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				start;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*is_eating_lock;
	pthread_t		thread;
	int				id;
	int				last_meal;
	int				meals_eaten;
	int				all_ate;
	int				is_dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;

}	t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	is_eating_lock[PHILO_MAX];
	pthread_t		monitor;
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				meals_to_eat;
	int				start;
}	t_data;

//Init
int		check_args(char **argv);
void	init_philo(t_data *data, t_philo *philo, char **argv);
void	init_forks(t_data *data, pthread_mutex_t *forks, t_philo *philo);
void	init(t_data *data, t_philo *philo, pthread_mutex_t *forks, char **argv);

//Philosophers
void	philosophers(t_data *data, t_philo *philo);
int		philo_is_not_dead(t_philo *philo);
int		philo_did_not_eat(t_philo *philo);
void	*routine(void *philo);

//Routine
void	eating(t_philo *philo);
void	eating2(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);

//Monitoring
int		philo_is_dead(t_philo *philos);
int		all_philo_ate(t_philo *philos);
void	assign_to_all_philos(t_philo *philo, int type);
void	*monitoring(void *pointer);

//Errors and prints
void	error_msg(char *str);
void	error_msg_clean_exit(char *str, t_data *data);
void	end_philo(t_data *data);

//Utils
int		is_numeric(char *str);
void	print_philo_state(char *str, t_philo *philo);
int		get_current_time(void);
void	ft_usleep(int nb, t_philo *philo);

#endif