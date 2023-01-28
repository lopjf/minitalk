/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:43:24 by loris             #+#    #+#             */
/*   Updated: 2022/10/17 12:44:54 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	convert_to_binary(int i, int pid, int count)
{
	while (i > 0)
	{
		if (i % 2 == 0)
			kill(pid, SIGUSR1);
		if (i % 2 == 1)
			kill(pid, SIGUSR2);
		usleep(100);
		i = i / 2;
		count++;
	}
	return (count);
}

int	main(int argc, char *argv[])
{
	int	i;
	int	pid;
	int	count;

	if (argc != 3)
		return (1);
	pid = ft_atoi(argv[1]);
	i = 0;
	count = convert_to_binary(ft_strlen(argv[2]), pid, 0);
	while (count++ < 31)
	{
		kill(pid, SIGUSR1);
		usleep(100);
	}
	ft_printf("\n");
	while (argv[2][i] != 0)
	{
		count = convert_to_binary(argv[2][i++], pid, 0);
		while (count++ < 8)
		{
			kill(pid, SIGUSR1);
			usleep(100);
		}
	}
	return (0);
}
