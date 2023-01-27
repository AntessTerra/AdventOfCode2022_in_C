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
		while (++i < 100)
			row[i] = 0;
	}
}

int	main(void)
{
	int		input_file;
	int		i;
	int		y;
	int		x;
	int		counter;
	int		move;
	int		sum;
	char	c;
	char	row[100];
	line	*map;
	point	start;
	point	*list;

	start.name = 's';
	start.x = 499;
	start.y = 499;
	list = malloc(sizeof(point) * 10);
	list[0].name = 'H';
	list[0].x = start.x;
	list[0].y = start.y;
	list[1].name = '1';
	list[1].x = start.x;
	list[1].y = start.y;
	counter = 2;
	while (counter < 10)
	{
		list[counter].name = list[counter - 1].name + 1;
		list[counter].x = start.x;
		list[counter].y = start.y;
		counter++;
	}
	map = malloc(sizeof(line) * 1000);
	y = 0;
	while (y < 1000)
	{
		x = 0;
		map[y].text = malloc(1000);
		while (x < 1000)
		{
			if (y == list[0].y && x == list[0].x)
			{
				map[y].text[x] = list[0].name;
			}
			else
				map[y].text[x] = '.';
			x++;
		}
		y++;
	}


	i = 0;

	reset(row, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			row[++i] = c;
		else
		{
			move = ft_atoi(row);
			while (move > 0)
			{
				//map[list[0].y].text[list[0].x] = '.';
				if (row[0] == 'U')
					list[0].y--;
				if (row[0] == 'D')
					list[0].y++;
				if (row[0] == 'L')
					list[0].x--;
				if (row[0] == 'R')
					list[0].x++;
				//map[list[0].y].text[list[0].x] = list[0].name;

				counter = 1;
				while (counter < 10)
				{
					while (list[counter - 1].x - list[counter].x > 1 || list[counter - 1].x - list[counter].x < -1 || list[counter - 1].y - list[counter].y > 1 || list[counter - 1].y - list[counter].y < -1)
					{
						//map[list[counter].y].text[list[counter].x] = '.';
						map[list[9].y].text[list[9].x] = '#';
						//UpRight
						if ((list[counter - 1].x - list[counter].x > 0 && list[counter - 1].y - list[counter].y < -1) || (list[counter - 1].x - list[counter].x > 1 && list[counter - 1].y - list[counter].y < 0))
						{
							list[counter].x++;
							list[counter].y--;
						}
						//UpLeft
						else if ((list[counter - 1].x - list[counter].x < 0 && list[counter - 1].y - list[counter].y < -1) || (list[counter - 1].x - list[counter].x < -1 && list[counter - 1].y - list[counter].y < 0))
						{
							list[counter].x--;
							list[counter].y--;
						}
						//DownRight
						else if ((list[counter - 1].y - list[counter].y > 1 && list[counter - 1].x - list[counter].x > 0) || (list[counter - 1].y - list[counter].y > 0 && list[counter - 1].x - list[counter].x > 1))
						{
							list[counter].y++;
							list[counter].x++;
						}
						//DownLeft
						else if ((list[counter - 1].y - list[counter].y > 1 && list[counter - 1].x - list[counter].x < 0) || (list[counter - 1].y - list[counter].y > 0 && list[counter - 1].x - list[counter].x < -1))
						{
							list[counter].y++;
							list[counter].x--;
						}

						//right
						else if (list[counter - 1].x - list[counter].x > 1)
						{
							list[counter].x++;
						}
						//left
						else if (list[counter - 1].x - list[counter].x < -1)
						{
							list[counter].x--;
						}
						//down
						else if (list[counter - 1].y - list[counter].y > 1)
						{
							list[counter].y++;
						}
						//up
						else if (list[counter - 1].y - list[counter].y < -1)
						{
							list[counter].y--;
						}
						//map[list[counter].y].text[list[counter].x] = list[counter].name;
					}
					//printf("Point%d y:%d|x:%d\n", counter, list[counter].y, list[counter].x);
					counter++;
				}
				move--;
			}
			reset(row, &i);
		}

	}
	map[list[9].y].text[list[9].x] = '#';
	map[start.y].text[start.x] = start.name;




	y = 0;
	while (y < 1000)
	{
		x = 0;
		while (x < 1000)
		{
			if (map[y].text[x] == '#' || map[y].text[x] == 's')
				sum++;
			x++;
		}
		//printf("%d:%s\n", y, map[y].text);
		y++;
	}

/*
	y = 0;
	while (y < 1000)
	{
		printf("%d:%s\n", y, map[y].text);
		y++;
	}
*/
	printf("Sum: %d", sum);
	close(input_file);
	return (1);
}
