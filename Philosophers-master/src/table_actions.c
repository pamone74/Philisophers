/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamone <pamone@student.42abudhabi.ae>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 12:26:25 by pamone            #+#    #+#             */
/*   Updated: 2024/03/22 14:48:02 by pamone           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"
//The two while loop in the take fork function checkes for two things
//First: Make the philo wait if the fork is -1(already taken)
//Second: It checks if the fork value if equal with the philo id 
//which mean if the fork was used by the same philosopher before(this will handle greedy philosopher case)

void	take_fork_even(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->fork_locker[philo->fork_right]);
	pthread_mutex_lock(&philo->data->fork_locker[philo->fork_left]);
	while (philo->data->fork[philo->fork_left] == -1 
			|| philo->data->fork[philo->fork_right] == -1
			|| philo->data->fork[philo->fork_right] == philo->id
			|| philo->data->fork[philo->fork_left] == philo->id)
	{
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_right]);
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_left]);
		usleep(100);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_right]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_left]);
	}
	philo->data->fork[philo->fork_left] = -1;
	philo->data->fork[philo->fork_right] = -1;
	pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_right]);
	pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_left]);
	display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
	display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
}

void	take_fork(t_philos *philo)
{
	if (philo->id % 2 != 0)
	{
		usleep(1500);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_left]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_right]);
		while (philo->data->fork[philo->fork_left] == -1 
				|| philo->data->fork[philo->fork_right] == -1
				|| philo->data->fork[philo->fork_right] == philo->id
				|| philo->data->fork[philo->fork_left] == philo->id)
		{
			pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_left]);
			pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_right]);
			usleep(100);
			pthread_mutex_lock(&philo->data->fork_locker[philo->fork_left]);
			pthread_mutex_lock(&philo->data->fork_locker[philo->fork_right]);
		}
		philo->data->fork[philo->fork_left] = -1;
		philo->data->fork[philo->fork_right] = -1;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_left]);
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_right]);
		display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
		display(philo, " \e[0;32m🥄 has taken  fork \033[0m", real_time(philo), 0);
	}
	else
		take_fork_even(philo);
}

void	eat_philo(t_philos *philo)
{
	pthread_mutex_lock(&philo->data->end_g);
	if (philo->data->end_game == 0)
	{
		pthread_mutex_unlock(&philo->data->end_g);
		take_fork(philo);
		display(philo, "\e[0;33m 🍽  is eating \033[0m", real_time(philo), 0);
		pthread_mutex_lock(&philo->data->last_meal_locker);
		philo->last_meal = timestamp();
		pthread_mutex_unlock(&philo->data->last_meal_locker);
		pthread_mutex_lock(&philo->data->num_meals_locker);
		philo->data->total_no_meals++;
		pthread_mutex_unlock(&philo->data->num_meals_locker);
		ft_usleep(philo->data->t_eat, philo);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_left]);
		philo->data->fork[philo->fork_left] = philo->id;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_left]);
		pthread_mutex_lock(&philo->data->fork_locker[philo->fork_right]);
		philo->data->fork[philo->fork_right] = philo->id;
		pthread_mutex_unlock(&philo->data->fork_locker[philo->fork_right]);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_g);
}

void	ft_usleep(long long t_2wait, t_philos *philo)
{
	long long	current_time;

	current_time = timestamp();
	pthread_mutex_lock(&philo->data->end_g);
	if (philo->data->end_game != 0)
	{
		pthread_mutex_unlock(&philo->data->end_g);
		return ;
	}
	pthread_mutex_unlock(&philo->data->end_g);
	while (timestamp() - current_time < t_2wait)
		usleep(100);
}
