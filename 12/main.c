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
	while (str[i] < '0' || str[i] > '9')
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

void	reset_temp(point *temp, int *counter)
{
	int	i;

	i = 0;
	if (counter)
		*counter = 0;
	if (temp)
	{
		while (i++ < 4)
		{
			temp[i].x = -1;
			temp[i].y = -1;
			temp[i].i = -1;
			temp[i].val = '\0';
		}
	}
}

int	main(void)
{
	int		input_file;
	int		i;
	int		y;
	int		x;
	int		z;
	int		l;
	int		nlist;
	int		counter;
	int		appendable;
	char	c;
	char	row[100];
	line	*map;
	point	*list;
	point	*temp;

	map = malloc(sizeof(line) * 5);
	y = 0;
	while (y < 5)
	{
		map[y++].text = malloc(10);
	}
	list = malloc(sizeof(point) * 10000);
	temp = malloc(sizeof(point) * 10);
	i = 0;
	y = 0;
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
			ft_strcpy(map[y].text, row);
			y++;
			reset(row, &i);
		}
	}
	//logic
	list[0].x = 5;
	list[0].y = 2;
	list[0].i = 0;
	list[0].val = 'z';
	counter = 1;
	nlist = 1;
	l = 0;
	//go trough elements list[l].val != 'S'
	while (list[l].val != 'S')
	{
		//1. create list of 4 adjacent points
		z = 0;
		if (list[l].x < 7)
		{
			temp[z].x = list[l].x + 1;
			temp[z].y = list[l].y;
			temp[z].i = counter;
			temp[z].val = map[list[l].y].text[list[l].x + 1];
			z++;
		}
		if (list[l].x > 0)
		{
			temp[z].x = list[l].x - 1;
			temp[z].y = list[l].y;
			temp[z].i = counter;
			temp[z].val = map[list[l].y].text[list[l].x - 1];
			z++;
		}
		if (list[l].y < 4)
		{
			temp[z].x = list[l].x;
			temp[z].y = list[l].y + 1;
			temp[z].i = counter;
			temp[z].val = map[list[l].y + 1].text[list[l].x];
			z++;
		}
		if (list[l].y > 0)
		{
			temp[z].x = list[l].x;
			temp[z].y = list[l].y - 1;
			temp[z].i = counter;
			temp[z].val = map[list[l].y - 1].text[list[l].x];
			z++;
		}
		//2. check for conditions

		x = 0;
		while (x < z)
		{

			if (temp[x].val == list[l].val || temp[x].val == list[l].val - 1 || temp[x].val == 'S')
			{
				//printf("Temp: %c|%d|%d|%d   |   %d\n", temp[x].val, temp[x].y, temp[x].x, temp[x].i, z);
				appendable = 1;
				y = 0;
				while (y < nlist)
				{
					if (temp[x].x == list[y].x && temp[x].y == list[y].y)
					{
						appendable = 0;
					}
					y++;
				}
				//3. append
				if (appendable)
				{
					list[nlist].x = temp[x].x;
					list[nlist].y = temp[x].y;
					list[nlist].i = temp[x].i;
					list[nlist].val = temp[x].val;
					nlist++;

				}
			}
			x++;
		}
		//4. next item in list
		l++;
		counter = list[l].i;
		counter++;
		reset_temp(temp, &z);
	}

	y = 0;
	while (y < nlist)
	{
		printf("List: %c|%d|%d|%d\n", list[y].val, list[y].y, list[y].x, list[y].i);
		y++;
	}

	close(input_file);
	return (1);
}
