/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhagon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 10:58:48 by juhagon           #+#    #+#             */
/*   Updated: 2022/02/07 12:19:09 by juhagon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/*
 * This function is called in the main every time a thread is created.
 * it is blocked with Mutex which means that the button will not be pressed
 *  until the other subject has finished pressing it.
 */

void	*create_guy(void	*vargp)
{
	static int	i = 1;

	pthread_mutex_lock(&vargp[0]);
	printf("I'm the subject number %d, and I will press the button now\n", i);
	i++;
	sleep(5);
	pthread_mutex_unlock(&vargp[0]);
	return (NULL);
}

/*
 * In the Main I create two Threads and Call the create_guy function passing 
 * the mutex lock variable as an argument
 */

int	main(void)
{
	pthread_t			thread_id[2];
	pthread_mutex_t		lock;
	int					i;

	i = 0;
	pthread_mutex_init(&lock, NULL);
	while (i < 2)
	{
		pthread_create(&(thread_id[i]), NULL, &create_guy, (void *)&lock);
		i++;
	}
	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);
	pthread_mutex_destroy(&lock);
	return (0);
}
