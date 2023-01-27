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
#include "./struct.h"

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
	while ((str[i] < '0' || str[i] > '9') && str[i] != '-')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		base = base * 10 + (str[i] - '0');
		i++;
	}
	return (base * sign);
}

int		ft_strlen(char *str)
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
		while (++i < 200)
			row[i] = 0;
	}
}

void	reset_temp(char *temp, int *counter)
{
	int	i;

	i = 0;
	if (counter)
		*counter = 0;
	if (temp)
	{
		while (i < 50)
			temp[i++] = 0;
	}
}

void	reset_point(point *temp, int *counter)
{
	int	i;

	i = 0;
	if (counter)
		*counter = 0;
	if (temp)
	{
		while (i++ < 30)
		{
			temp[i].x = 0;
			temp[i].y = 0;
		}
	}
}

void	reset_test(line *test, int *counter)
{
	int	i;

	i = 0;
	if (counter)
		*counter = 0;
	if (test)
	{
		while (i++ < 8000000)
		{
			test[0].text[i] = '.';
		}
	}
}

int	main(void)
{
	int		input_file;
	int		i;
	int		l;
	int		r;
	int		z;
	int		y;
	int		x;
	int		h;
	int		count;
	int		appendable;
	int		t;
	int		cycle;
	int		manhaton;
	int		mx;
	int		my;
	int		maxhash;
	int		sum;
	int		locnum;
	char	c;
	char	row[200];
	char	left[50];
	char	right[50];
	line	test;
	point	*beacon;
	point	*sensor;
	hash	*hash;
	point	*temp;

	test.text = malloc(8000001);
	x = 0;
	while (x < 8000000)
	{
		test.text[x] = '.';
		x++;
	}

	temp = malloc(sizeof(point) * 10);
	beacon = malloc(sizeof(point) * 30);
	sensor = malloc(sizeof(point) * 30);
	i = 0;
	reset(row, &i);
	l = 0;
	r = 0;


	reset_temp(left, &l);
	reset_temp(right, &r);
	input_file = open("inputLarge", O_RDONLY);
	count = 0;
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			row[++i] = c;
		else
		{
			z = 0;
			while (row[z] != ',')
			{
				left[l++] = row[z++];
			}
			while (row[z] != ':')
			{
				right[r++] = row[z++];
			}
			x = ft_atoi(left) + 2000000;
			y = ft_atoi(right);
			//printf("SENSOR :    LEFT: %s | RIGHT: %s\n", left, right);
			sensor[count].x = x;
			sensor[count].y = y;

			reset_temp(left, &l);
			reset_temp(right, &r);

			while (row[z] != ',')
			{
				left[l++] = row[z++];
			}
			while (z < ft_strlen(row))
			{
				right[r++] = row[z++];
			}
			x = ft_atoi(left) + 2000000;
			y = ft_atoi(right);
			//printf("BEACON :    LEFT: %s | RIGHT: %s\n", left, right);
			beacon[count].x = x;
			beacon[count].y = y;

			reset_temp(left, &l);
			reset_temp(right, &r);

			reset(row, &i);
			count++;

		}
	}
	x = 3230812;
	while (x < 4000000)
	{
		sum = 0;
		y = 0;
		while (y < count)
		{
			mx = sensor[y].x - beacon[y].x;
			if (mx < 0)
				mx = mx * -1;
			my = sensor[y].y - beacon[y].y;
			if (my < 0)
				my = my * -1;
			manhaton = mx + my;
			locnum = sensor[y].y - x;
			if (locnum < 0)
				locnum = locnum * -1;
			//printf("Sensor%d: %d|%d  Beacon%d: %d|%d  Manhaton: %d  Locnum: %d\n", y, sensor[y].x, sensor[y].y, x, beacon[y].x, beacon[y].y, manhaton, locnum);
			if (manhaton >= locnum)
			{
				t = manhaton - locnum;
				while (t >= 0)
				{
					test.text[sensor[y].x + t] = '#';
					test.text[sensor[y].x - t] = '#';
					t--;
				}

			}
			y++;
		}
		h = 2000000;
		while (h < 6000000)
		{
			if (test.text[h] == '.')
			{
				printf("Space at %d\n", h - 2000000);
			}

			h++;
		}
		if (sum < 4000000)
		{
			printf("Found a space at :%d | Sum: %d\n", x, sum);
			break;
		}
		if (x % 10000 == 0)
			printf("Im %dprocent done\n", x / 10000);
		h = 0;
		while (h < 8000000)
		{
			test.text[h] = '.';
			h++;
		}
		x++;
	}
	/*
	//area
			mx = sensor[count].x - beacon[count].x;
			if (mx < 0)
				mx = mx * -1;
			my = sensor[count].y - beacon[count].y;
			if (my < 0)
				my = my * -1;
			manhaton = mx + my;
			locnum = sensor[count].y - 2000000;
			if (locnum < 0)
				locnum = locnum * -1;
			if (manhaton >= locnum)
			{
				printf("Sensor: %d|%d  Beacon: %d|%d  Manhaton: %d  Locnum: %d\n", sensor[count].x, sensor[count].y, beacon[count].x, beacon[count].y, manhaton, locnum);
				x = manhaton - locnum;
				while (x >= 0)
				{
					test.text[sensor[count].x + x] = '#';
					test.text[sensor[count].x - x] = '#';
					x--;
				}


			}
	*/
	//count
	/*
	x = 0;
	while (x < 8000000)
	{
		if (test.text[x] == '#')
			sum++;
		x++;
	}
	printf("SUM: %d\n", sum);
	*/
	//printf("Test: %s", test.text);
	close(input_file);
	return (1);
}
