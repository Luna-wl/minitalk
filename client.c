/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluedara <wluedara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:18:52 by wluedara          #+#    #+#             */
/*   Updated: 2023/02/24 14:59:29 by wluedara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_sending(int mode)
{
	if (mode == 1)
		write(1, BLU"Error occurred during send SIGUSR1 (๏ᆺ๏υ)\n" RESET, 53);
	else
		write(1, CYA"Error occurred during send SIGUSR2 (●´⌓`●)\n" RESET, 54);
	exit(EXIT_FAILURE);
}

void	int_to_bit(int c)
{
	int	i;
	int	bit;

	i = 8;
	while (i-- > 0)
	{
		bit = c >> i;
		if (bit & 1)
		{
			if (kill(g_client.pid, SIGUSR1) != 0)
				error_sending(1);
		}
		else
		{
			if (kill(g_client.pid, SIGUSR2) != 0)
				error_sending(0);
		}
		usleep(50);
	}
}

void	send_msg(char *s)
{
	while (*s)
	{
		int_to_bit(*s);
		s++;
	}
}

int	main(int ac, char **av)
{
	struct sigaction	sig;

	if (ac != 3)
	{
		write(1, RED"You put wrong input ⊙▂⊙\n"RESET, 35);
		exit(EXIT_FAILURE);
	}
	while (*av[1] >= '0' && *av[1] <= '9')
	{
		g_client.pid = (g_client.pid * 10) + (*av[1] - 48);
		av[1]++;
	}
	if (g_client.pid <= 0)
	{
		write(1, YEL"You shouldn't do this! (⌐■_■)\n"RESET, 41);
		exit(EXIT_FAILURE);
	}
	sigaction(SIGUSR1, &sig, NULL);
	send_msg(av[2]);
	return (0);
}
