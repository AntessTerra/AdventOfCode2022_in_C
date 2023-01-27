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
		while (i++ < 10)
		{
			temp[i].x = 1;
			temp[i].y = 1;
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
	int		hashcount;
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
	point	beacon;
	point	sensor;
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
	i = 0;
	reset(row, &i);
	l = 0;
	r = 0;
	sum = 0;

	reset_temp(left, &l);
	reset_temp(right, &r);
	input_file = open("inputLarge", O_RDONLY);
	hashcount = 0;
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
			sensor.x = x;
			sensor.y = y;

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
			beacon.x = x;
			beacon.y = y;

			reset_temp(left, &l);
			reset_temp(right, &r);

			//area






			mx = sensor.x - beacon.x;
			if (mx < 0)
				mx = mx * -1;
			my = sensor.y - beacon.y;
			if (my < 0)
				my = my * -1;
			manhaton = mx + my;
			locnum = sensor.y - 2000000;
			if (locnum < 0)
				locnum = locnum * -1;
			if (manhaton >= locnum)
			{
				printf("Sensor: %d|%d  Beacon: %d|%d  Manhaton: %d  Locnum: %d\n", sensor.x, sensor.y, beacon.x, beacon.y, manhaton, locnum);
				x = manhaton - locnum;
				while (x >= 0)
				{
					test.text[sensor.x + x] = '#';
					test.text[sensor.x - x] = '#';
					x--;
				}


				if (beacon.y == 2000000)
				{
					printf("Beacon: %d\n", beacon.x);
					test.text[beacon.x] = 'B';
				}
			}

			/*
			cycle = 1;
			h = 1;

			while (cycle <= maxhash)
			{

				t = 0;
				//get adjacent
				temp[t].x = hash[hashcount].p[cycle - 1].x - 1;
				temp[t].y = hash[hashcount].p[cycle - 1].y;
				t++;

				temp[t].x = hash[hashcount].p[cycle - 1].x + 1;
				temp[t].y = hash[hashcount].p[cycle - 1].y;
				t++;

				temp[t].x = hash[hashcount].p[cycle - 1].x;
				temp[t].y = hash[hashcount].p[cycle - 1].y - 1;
				t++;;

				temp[t].x = hash[hashcount].p[cycle - 1].x;
				temp[t].y = hash[hashcount].p[cycle - 1].y + 1;
				t++;

				//append
				x = 0;
				while (x < t)
				{
					appendable = 1;
					y = 0;
					while (y < h)
					{
						if (temp[x].x == hash[hashcount].p[y].x  && temp[x].y == hash[hashcount].p[y].y )
						{
							appendable = 0;
						}
						y++;
					}

					if (appendable)
					{
						hash[hashcount].p[h].x = temp[x].x;
						hash[hashcount].p[h].y = temp[x].y;
						h++;
					}
					x++;
				}
				//printf("H: %d\n", h);

				cycle++;
				reset_point(temp, &t);
			}
			hash[hashcount].nhash = h;
			hashcount++;
			*/
			reset(row, &i);

		}
	}
	//draw
	/*
	x = 0;
	while (x < hashcount)
	{
		y = 1;
		while (y < hash[x].nhash)
		{
			if (map[hash[x].p[y].y].text[hash[x].p[y].x] != 'B')
				map[hash[x].p[y].y].text[hash[x].p[y].x] = '#';
			//printf("H: %d|%d   | %d\n", hash[x].p[y].y, hash[x].p[y].x, y);
			y++;
		}
		x++;
	}

	//count
	x = 0;
	while (x < 200)
	{
		if (map[110].text[x] == '#')
			sum++;
		x++;
	}
	printf("\n\n\n");
	y = 0;
	while (y < 200)
	{
		printf("%s :%d\n", map[y].text, y);
		y++;
	}
	printf("\n\n\n");
	printf("SUM: %d\n", sum);
	*/
	//count
	x = 0;
	while (x < 8000000)
	{
		if (test.text[x] == '#')
			sum++;
		x++;
	}
	printf("SUM: %d\n", sum);
	//printf("Test: %s", test.text);
	close(input_file);
	return (1);
}
