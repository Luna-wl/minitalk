/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluedara <wluedara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:18:50 by wluedara          #+#    #+#             */
/*   Updated: 2023/02/23 22:34:38 by wluedara         ###   ########.fr       */
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

void	print_msg(int mode)
{
	static int	i = 0;

	i++;
	if (mode == 1)
	{
		g_server.ch += 1;
		if (i == 8)
		{
			write(1, &g_server.ch, 1);
			g_server.ch = 0;
			i = 0;
		}
	}
	else if (mode == 0)
	{
		g_server.ch += 0;
		if (i == 8)
		{
			write(1, &g_server.ch, 1);
			g_server.ch = 0;
			i = 0;
		}
	}
	g_server.ch <<= 1;
}

void	sig_handler(int signum, siginfo_t *sa, void *old)
{
	(void)old;

	if (signum == SIGUSR1)
	{
		print_msg(1);
	}
	else if (signum == SIGUSR2)
	{
		print_msg(0);
	}
}

int	main()
{
	struct sigaction	sig;

	g_server.pid = getpid();
	write(1, GRN"pid = ", 11);
	put_num(g_server.pid);
	write(1, "\n", 1);
	write(1, RESET, 5);
	g_server.ch = 0;
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
