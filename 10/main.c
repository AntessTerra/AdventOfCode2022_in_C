/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbartosi <xhelp00@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:27:36 by jbartosi          #+#    #+#             */
/*   Updated: 2022/10/30 21:19:43 by jbartosi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	base;
	int	sign;

	i = 0;
	base = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 'A' && str[i] <= 'z'))
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		base = base * 10 + (str[i] - '0');
		i++;
	}
	return (base * sign);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	reset(char *row, int *counter)
{
	int	i;

	i = -1;
	if (counter)
		*counter = -1;
	if (row)
	{
		while (++i < 100)
			row[i] = 0;
	}
}

int	main(void)
{
	int		input_file;
	int		i;
	int		cycle;
	int		x;
	int		sum;
	char	c;
	char	row[100];

	i = 0;
	cycle = 1;
	x = 1;
	sum = 0;
	reset(row, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
		{
			row[++i] = c;
		}
		else
		{
			if (row[0] == 'n')
			{
				if (cycle % 40 == 20 && cycle <= 220)
				{
					sum = sum + x * cycle;
					printf("Cycle %d: %d\n", cycle, x * cycle);
				}
				cycle++;
			}
			else
			{
				if (cycle % 40 == 20 && cycle <= 220)
				{
					sum = sum + x * cycle;
					printf("Cycle %d: %d\n", cycle, x * cycle);
				}
				cycle++;
				if (cycle % 40 == 20 && cycle <= 220)
				{
					sum = sum + x * cycle;
					printf("Cycle %d: %d\n", cycle, x * cycle);
				}
				x = x + ft_atoi(row);
				cycle++;

			}
			reset(row, &i);
		}
	}
	printf("Sum: %d\n", sum);
	close(input_file);
	return (1);
}
