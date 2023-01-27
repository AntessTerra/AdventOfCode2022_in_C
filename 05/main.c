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
	while (str[i] == ' ' || (str[i] >= 97 && str[i] <= 122))
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

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(void)
{
	int		input_file;
	int		i;
	int		counter;
	int		move;
	int		from;
	int		to;
	int		x;
	char	*ar[50];
	char	c;
	char	line[100];

	i = 0;
	counter = 0;
	move = 0;
	from = 0;
	to = 0;
	reset(line, &i);
	while (counter < 9)
	{
		ar[counter++] = malloc(50);
	}
	counter = 0;
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n' && counter < 9)
			line[++i] = c;
		else if (counter < 9)
		{
			ft_strcpy(ar[counter++], line);
			reset(line, &i);
		}
		else if (c == 'f')
		{
			move = ft_atoi(line);
			reset(line, &i);
		}
		else if (c == 't')
		{
			from = ft_atoi(line);
			reset(line, &i);
		}
		else if (c == '\n')
		{
			to = ft_atoi(line);
			reset(line, &i);
			printf("-----------------\n%d|%d|%d\n", move, from, to);
			//Part 1
			/*
			x = 0;
			while (x < move)
			{
				ar[to - 1][ft_strlen(ar[to - 1])] = ar[from - 1][ft_strlen(ar[from - 1]) - 1];
				ar[from - 1][ft_strlen(ar[from - 1]) - 1] = '\0';
				x++;
			}
			*/

			//Part 2
			x = move;
			while (x > 0)
			{
				ar[to - 1][ft_strlen(ar[to - 1])] = ar[from - 1][ft_strlen(ar[from - 1]) - x];
				x--;
			}
			x = move;
			while (x > 0)
			{
				ar[from - 1][ft_strlen(ar[from - 1]) - 1] = '\0';
				x--;
			}

			counter = 0;
			while (counter < 9)
			{
				printf("Line%d: %s\n", counter + 1, ar[counter]);
				counter++;
			}
		}
		else if (c != '\n')
		{
			line[++i] = c;
		}
	}
	//counter = 0;
	//while (counter < 9)
	//{
	//	printf("Line: %s\n", ar[counter++]);
	//}
	close(input_file);
	return (1);
}
