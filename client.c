/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nterziog <nterziog@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/15 14:27:41 by nterziog          #+#    #+#             */
/*   Updated: 2023/02/03 18:51:29 by nterziog         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	register int	iter;
	register int	result;

	iter = 0;
	result = 0;
	while ((str[iter] >= '\t' && str[iter] <= '\r') || str[iter] == ' ')
		iter++;
	while (str[iter] >= '0' && str[iter] <= '9' && str[iter] != '\0')
		result = ((str[iter++] - '0') + (result * 10));
	return (result);
}

void	send_data(char c, int pid)
{
	int	index;

	index = 0;
	while (index < 8)
	{
		if (c << index & 0b10000000)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		index++;
		usleep(400);
	}
}

int	main(int ac, char *av[])
{
	int	pid;
	int	index;

	index = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		while (av[2][index] != '\0')
		{
			send_data(av[2][index++], pid);
		}
	}
	else
		ft_printf("CLIENT : FORMAT Error!\nSend as ./client <PID> <MESSAGE>\n");
	return (0);
}
