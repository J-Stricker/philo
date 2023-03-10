/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsariogl <fsariogl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 15:23:53 by fsariogl          #+#    #+#             */
/*   Updated: 2023/02/16 17:48:06 by fsariogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	get_finish_state(t_philo *philo)
{
	pthread_mutex_lock(&(*philo).mutex_state);
	if ((*philo).state != DEAD && (*philo).state != STOP)
		(*philo).state = FINISH_EAT;
	pthread_mutex_unlock(&(*philo).mutex_state);
}

void	sleep_time(t_philo *philo)
{
	int	state_bis;

	pthread_mutex_lock(&(*philo).mutex_state);
	state_bis = (*philo).state;
	pthread_mutex_unlock(&(*philo).mutex_state);
	usleep((*philo).philo_no);
	if (state_bis != DEAD && state_bis != STOP)
		print_state(philo, (*philo).philo_no + 1, 1);
	if ((*philo).eat_nb >= (*philo).minimum_eat && (*philo).minimum_eat != -1
		&& state_bis != DEAD)
		get_finish_state(philo);
	(*philo).start_sleep = get_timestamp();
	while (1)
	{
		pthread_mutex_lock(&(*philo).mutex_state);
		state_bis = (*philo).state;
		pthread_mutex_unlock(&(*philo).mutex_state);
		if (new_timestamp((*philo).start_sleep) >= (*philo).time_to_sleep
			|| state_bis == STOP || state_bis == DEAD)
			break ;
		usleep(100);
	}
}
