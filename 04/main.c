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

int	ft_atoi(const char *str)
{
	int	i;
	int	base;
	int	sign;

	i = 0;
	base = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
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

void	reset(char *line, int *counter)
{
	int	i;

	i = -1;
	if (counter)
		*counter = -1;
	if (line)
	{
		while (++i < 100)
			line[i] = 0;
	}
}

int		incase(int *ar)
{
	if (ar[2] >= ar[0] && ar[3] <= ar[1])
		return (1);
	else if (ar[2] <= ar[0] && ar[3] >= ar[1])
		return (1);
	else
		return (0);
}

int		overlap(int *ar)
{
	if (ar[1] < ar[2])
		return (0);
	else if (ar[3] < ar[0])
		return (0);
	else
		return (1);
}

int	main(void)
{
	int		input_file;
	int		i;
	int		ar[4];
	int		counter;
	int		sum;
	char	c;
	char	line[100];

	i = 0;
	counter = 0;
	sum = 0;
	reset(line, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c == '-' && counter == 0)
		{
			ar[counter++] = ft_atoi(line);
			reset(line, &i);
		}
		else if (c == ',' && counter == 1)
		{
			ar[counter++] = ft_atoi(line);
			reset(line, &i);
		}
		else if (c == '-' && counter == 2)
		{
			ar[counter++] = ft_atoi(line);
			reset(line, &i);
		}
		else if (c != '\n')
			line[++i] = c;
		else
		{
			ar[counter] = ft_atoi(line);
			reset(line, &i);
			counter = 0;
			sum = sum + overlap(ar);
			printf("Line: %d - %d , %d - %d\n", ar[0], ar[1], ar[2], ar[3]);
			printf("Overlap: %d\n", sum);
		}
	}
	close(input_file);
	return (1);
}
