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

int		ft_atoi(const char *str)
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
		while (++i < 1000)
			row[i] = 0;
	}
}

int	main(void)
{
	int		input_file;
	int		i;
	int		x;
	int		y;
	int		j;
	int		k;
	int		counter;
	int		visible;
	int		points;
	int		pointed;
	int		score;
	char	c;
	char	row[1000];
	line	*map;

	map = malloc(sizeof(line) * 200);
	i = 0;
	counter = 0;
	visible = 0;
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
			map[counter].text = malloc(200);
			ft_strcpy(map[counter].text, row);
			counter++;
			reset(row, &i);
		}
	}
	//Part 1
	/*
	y = 0;
	while (y < counter)
	{
		x = 0;
		while (x < ft_strlen(map[y].text))
		{
			if (x == 0 || x == ft_strlen(map[y].text) - 1 || y == 0 || y == counter - 1)
				visible++;
			else
			{
				points = 0;
				j = x;
				pointed = 0;
				while (j > 0)
				{
					if (map[y].text[j - 1]  >= map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					j--;
				}
				//printf("Y:%d|X:%d|Points: %d  ", y, x, points);
				j = x;
				pointed = 0;
				while (j < ft_strlen(map[y].text) - 1)
				{
					if (map[y].text[j + 1] >= map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					j++;
				}
				//printf("Y:%d|X:%d|Points: %d  ", y, x, points);
				k = y;
				pointed = 0;
				while (k > 0)
				{
					if (map[k - 1].text[x] >= map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					k--;
				}
				//printf("Y:%d|X:%d|Points: %d  ", y, x, points);
				k = y;
				pointed = 0;
				while (k < counter - 1)
				{
					if (map[k + 1].text[x] >= map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					k++;
				}
				//printf("Y:%d|X:%d|Points: %d  ", y, x, points);

				if (points < 4)
					visible++;
				//printf("Num visible:%d\n", visible);
			}
			x++;
		}
		y++;
	}
	printf("Num visible:%d\n", visible);
	*/
	y = 0;
	while (y < counter)
	{
		x = 0;
		while (x < ft_strlen(map[y].text))
		{
			if (x == 0 || x == ft_strlen(map[y].text) - 1 || y == 0 || y == counter - 1)
				visible++;
			else
			{
				score = 1;
				points = 0;
				j = x;
				pointed = 0;
				while (j > 0)
				{
					if (map[y].text[j - 1] <= map[y].text[x] && pointed == 0)
					{
						points++;
						if (map[y].text[j - 1] == map[y].text[x])
							pointed = 1;
					}
					else if (map[y].text[j - 1] > map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					j--;
				}
				score = score * points;
				//printf("Y:%d|X:%d|LeftPoints: %d  ", y, x, points);
				points = 0;

				j = x;
				pointed = 0;
				while (j < ft_strlen(map[y].text) - 1)
				{
					if (map[y].text[j + 1] <= map[y].text[x] && pointed == 0)
					{
						points++;
						if (map[y].text[j + 1] == map[y].text[x])
							pointed = 1;
					}
					else if (map[y].text[j + 1] > map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					j++;
				}
				score = score * points;
				//printf("RightPoints: %d  ", points);
				points = 0;
				k = y;
				pointed = 0;
				while (k > 0)
				{
					if (map[k - 1].text[x] <= map[y].text[x] && pointed == 0)
					{
						points++;
						if (map[k - 1].text[x] == map[y].text[x])
							pointed = 1;
					}
					else if (map[k - 1].text[x] > map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					k--;
				}
				score = score * points;
				//printf("UpPoints: %d  ", points);
				points = 0;
				k = y;
				pointed = 0;
				while (k < counter - 1)
				{
					if (map[k + 1].text[x] <= map[y].text[x] && pointed == 0)
					{
						points++;
						if (map[k + 1].text[x] == map[y].text[x])
							pointed = 1;
					}
					else if (map[k + 1].text[x] > map[y].text[x] && pointed == 0)
					{
						points++;
						pointed = 1;
					}
					k++;
				}
				score = score * points;
				//printf("DownPoints: %d  ", points);
				points = 0;
				if (score > 200000)
					printf("||Final Score:%d\n", score);

			}
			x++;
		}
		y++;
	}


	/*
	x = 0;
	while (x < counter)
	{
		printf("Line%d: %s\n", x, map[x].text);
		x++;
	}
	*/
	close(input_file);
	return (1);
}
