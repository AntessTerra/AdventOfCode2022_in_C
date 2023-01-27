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

void	ft_sort(int *tab, int size)
{
	int	i;
	int	c;
	int	f;
	int	s;
	int	tmp;

	i = 0;
	while (i != (size - 1))
	{
		c = 0;
		while (c != (size - 1))
		{
			f = tab[c];
			s = tab[c + 1];
			if (f > s)
			{
				tmp = tab[c];
				tab[c] = tab[c + 1];
				tab[c + 1] = tmp;
			}
			c++;
		}
		i++;
	}
	i = 0;
	while (i < size - 1)
	{
		printf("num: %d \n", tab[i++]);
	}
	printf("Lagrest num: %d \n", tab[size - 1]);
}

int	main(void)
{
	int		input_file;
	int		i;
	int		sum;
	int		count;
	int		ar[300];
	char	line[100];
	char	c;
	char	l;

	i = 0;
	sum = 0;
	count = 1;
	reset(line, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			line[++i] = c;
		else if (l == '\n')
		{
			//printf("Elf nuber %d: %d \n", count++, sum);
			ar[count++] = sum;
			sum = 0;
		}
		else
		{
			sum = sum + ft_atoi(line);
			reset(line, &i);
		}
		l = c;
	}
	//sort
	ft_sort(ar, count);
	//print first line

	close(input_file);
	return (1);
}
