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
	//int		s;
	int		sum;
	char	c;
	char	row[100];
	line	*map;
	point	head;
	//point	start;
	point	tail;

	head.name = 'H';
	head.x = 499;
	head.y = 499;
	//start.name = 's';
	//start.x = head.x;
	//start.y = head.y;
	tail.name = 'T';
	tail.x = head.x;
	tail.y = head.y;
	map = malloc(sizeof(line) * 1000);
	y = 0;
	while (y < 1000)
	{
		x = 0;
		map[y].text = malloc(1000);
		while (x < 1000)
		{
			if (y == head.y && x == head.x)
			{
				map[y].text[x] = head.name;
			}
			else
				map[y].text[x] = '.';
			x++;
		}
		y++;
	}


	i = 0;
	//s = 0;
	reset(row, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			row[++i] = c;
		else
		{
			//move head
			if (row[0] == 'U')
			{
				//map[head.y].text[head.x] = '.';
				head.y = head.y - ft_atoi(row);
				//map[head.y].text[head.x] = head.name;
			}
			if (row[0] == 'D')
			{
				//map[head.y].text[head.x] = '.';
				head.y = head.y + ft_atoi(row);
				//map[head.y].text[head.x] = head.name;
			}
			if (row[0] == 'L')
			{
				//map[head.y].text[head.x] = '.';
				head.x = head.x - ft_atoi(row);
				//map[head.y].text[head.x] = head.name;
			}
			if (row[0] == 'R')
			{
				//map[head.y].text[head.x] = '.';
				head.x = head.x + ft_atoi(row);
				//map[head.y].text[head.x] = head.name;
			}
			printf("Head y:%d|x:%d  ", head.y, head.x);



			//tail follow
			while (head.x - tail.x > 1 || head.x - tail.x < -1 || head.y - tail.y > 1 || head.y - tail.y < -1)
			{
				map[tail.y].text[tail.x] = '#';
				//UpRight
				if ((head.x - tail.x > 0 && head.y - tail.y < -1) || (head.x - tail.x > 1 && head.y - tail.y < 0))
				{
					tail.x++;
					tail.y--;
				}
				//UpLeft
				else if ((head.x - tail.x < 0 && head.y - tail.y < -1) || (head.x - tail.x < -1 && head.y - tail.y < 0))
				{
					tail.x--;
					tail.y--;
				}
				//DownRight
				else if ((head.y - tail.y > 1 && head.x - tail.x > 0) || (head.y - tail.y > 0 && head.x - tail.x > 1))
				{
					tail.y++;
					tail.x++;
				}
				//DownLeft
				else if ((head.y - tail.y > 1 && head.x - tail.x < 0) || (head.y - tail.y > 0 && head.x - tail.x < -1))
				{
					tail.y++;
					tail.x--;
				}

				//right
				else if (head.x - tail.x > 1)
				{
					tail.x++;
				}
				//left
				else if (head.x - tail.x < -1)
				{
					tail.x--;
				}
				//down
				else if (head.y - tail.y > 1)
				{
					tail.y++;
				}
				//up
				else if (head.y - tail.y < -1)
				{
					tail.y--;
				}

				//map[tail.y].text[tail.x] = tail.name;
			}

			printf("Tail y:%d|x:%d\n", tail.y, tail.x);

			reset(row, &i);
		}
	}
	map[tail.y].text[tail.x] = '#';
/*
	if (s == 0)
	{
		map[start.y].text[start.x] = start.name;
		s = 1;
	}
*/

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
		//printf("%d:%s\n", y + 1, map[y].text);
		y++;
	}

	printf("Sum: %d", sum);
	close(input_file);
	return (1);
}
