

#include "../header/philosopher.h"

void take_fork(t_platon *philo, int r_fork, int l_fork)
{	
	if ((philo->id % 2) == 0)
	{
		usleep(1000);
		pthread_mutex_lock(&philo->data->forks[l_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
	}
	else if ((philo->id % 2) != 0)
	{
		pthread_mutex_lock(&philo->data->forks[r_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
		pthread_mutex_lock(&philo->data->forks[l_fork]);
		if (!mutexcopyb(&philo->data->dead, &philo->data->dead_man))
			mutexprint(philo, MS1);
	}
}
