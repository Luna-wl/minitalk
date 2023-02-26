/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluedara <Warintorn_L@outlook.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:18:50 by wluedara          #+#    #+#             */
/*   Updated: 2023/02/26 21:43:35 by wluedara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	put_num(int num)
{
	char	n;

	if (num > 9)
		put_num(num / 10);
	n = (num % 10) + 48;
	write(1, &n, 1);
}

void	reset_value(int ch)
{
	if (ch == 0)
	{
		if (kill(g_client.pid, SIGUSR1) != 0)
		{
			ft_putstr_fd(BLU"Something went wrong while receive message \
			¯\\_(ツ)_/¯\n"RESET, 2);
			exit(EXIT_FAILURE);
		}
	}
	write(1, &ch, 1);
}

void	print_msg(int mode)
{
	static int	i = 0;
	static int	ch = 0;

	i += 1;
	if (mode == 1)
		ch += 1;
	else if (mode == 0)
		ch += 0;
	if (i == 8)
	{
		reset_value(ch);
		ch = 0;
		i = 0;
	}
	ch <<= 1;
}

void	sig_handler(int signum, siginfo_t *sa, void *old)
{
	(void)old;
	g_client.pid = sa->si_pid;
	if (signum == SIGUSR1)
	{
		print_msg(1);
	}
	else if (signum == SIGUSR2)
	{
		print_msg(0);
	}
}

int	main(void)
{
	struct sigaction	sig;

	g_server.pid = getpid();
	write(1, GRN"pid = ", 11);
	put_num(g_server.pid);
	write(1, "\n", 1);
	write(1, RESET, 5);
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = sig_handler;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		usleep(2);
	}
}
