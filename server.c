/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wluedara <Warintorn_L@outlook.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 15:18:50 by wluedara          #+#    #+#             */
/*   Updated: 2023/02/19 16:53:41 by wluedara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	put_str(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	put_num(int num)
{
	char	n;

	if (num > 9)
		put_num(num / 10);
	n = (num % 10) + 48;
	write(1, &n, 1);
}

int	main()
{
	int pid;

	pid = getpid();
	put_str(PP"pid = ");
	put_num(pid);
	write(1, RESET, 5);
	while (1)
	{
		usleep(2);
	}
}