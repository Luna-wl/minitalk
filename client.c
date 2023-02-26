/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluedara <Warintorn_L@outlook.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:18:52 by wluedara          #+#    #+#             */
/*   Updated: 2023/02/26 21:43:48 by wluedara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	error_sending(int mode)
{
	if (mode == 1)
		ft_putstr_fd(BLU"Error occurred during send SIGUSR1 (๏ᆺ๏υ)\n"RESET, 2);
	else
		ft_putstr_fd(CYA"Error occurred during send SIGUSR2 (●´⌓`●)\n"RESET, 2);
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
	int_to_bit(*s);
}

void	signal_handler(int signum)
{
	ft_putstr_fd(CYA"message sending success (~￣³￣)~\n"RESET, 2);
}

int	main(int ac, char **av)
{
	if (ac != 3)
	{
		ft_putstr_fd(RED"You put wrong input ⊙▂⊙\n"RESET, 2);
		exit(EXIT_FAILURE);
	}
	while (*av[1] >= '0' && *av[1] <= '9')
	{
		g_client.pid = (g_client.pid * 10) + (*av[1] - 48);
		av[1]++;
	}
	if (g_client.pid <= 0)
	{
		ft_putstr_fd(YEL"You shouldn't do this! (⌐■_■)\n"RESET, 2);
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, signal_handler);
	send_msg(av[2]);
	return (0);
}
