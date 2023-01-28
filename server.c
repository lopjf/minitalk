/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loris <loris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 12:43:26 by loris             #+#    #+#             */
/*   Updated: 2022/10/17 12:44:55 by loris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_string(char *b, size_t j, int i, int f)
{
	static char	binary[9];

	while (i < 8)
		binary[i++] = b[j++];
	binary[8] = '\0';
	i = 0;
	while (f > 0)
		i = i * 2 + (binary[--f] - 48);
	ft_printf("%c", i);
}

static void	add_string(char c, size_t j)
{
	static char	*b;

	if (!b)
		b = (char *)ft_calloc(sizeof(char), (g_f - 31 + 1));
	if (ft_strlen(b) < g_f - 31)
		b[ft_strlen(b)] = c;
	b[ft_strlen(b)] = '\0';
	if (ft_strlen(b) == g_f - 31)
	{
		while (j < g_f - 31)
		{
			print_string(b, j, 0, 8);
			j += 8;
		}
		ft_printf("\n");
		b[0] = '\n';
		b = NULL;
		free(b);
		g_f = 0;
	}
}

static void	set_lenght(char c, int i, int slen)
{
	static char	*len;
	static char	*rev;

	if (!len)
		len = (char *)ft_calloc(sizeof(char), 31 + 1);
	if (ft_strlen(len) < 31)
		len[ft_strlen(len)] = c;
	len[ft_strlen(len)] = '\0';
	g_f++;
	if (g_f == 31)
	{
		rev = ft_revert(len);
		while (i < 31)
			slen = slen * 2 + (rev[i++] - 48);
		free(rev);
		len = NULL;
		free(len);
		g_f = (slen * 8) + 31;
	}
}

static void	handle_sigusr(int signal)
{
	static char	c;

	if (signal == SIGUSR1)
		c = '0';
	if (signal == SIGUSR2)
		c = '1';
	if (g_f < 31)
		set_lenght(c, 0, 0);
	else
		add_string(c, 0);
}

int	main(void)
{	
	ft_printf("%i\n", (int)getpid());
	signal(SIGUSR1, handle_sigusr);
	signal(SIGUSR2, handle_sigusr);
	while (1)
		pause();
	return (0);
}
