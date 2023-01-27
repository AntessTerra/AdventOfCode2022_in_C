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
		while (i < 20)
			temp[i++] = 0;
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
	int		hor;
	int		ver;
	int		movable;
	int		counter;
	char	c;
	char	row[200];
	char	left[20];
	char	right[20];
	line	*map;
	point	sand;


	map = malloc(sizeof(line) * 200);
	y = 0;
	while (y < 200)
	{
		x = 0;
		map[y].text = malloc(201);
		while (x < 200)
		{
			map[y].text[x] = '.';
			x++;
		}
		y++;
	}
	map[0].text[100] = '+';

	i = 0;
	reset(row, &i);
	l = 0;
	r = 0;

	reset_temp(left, &l);
	reset_temp(right, &r);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			row[++i] = c;
		else
		{
			z = 0;
			hor = 0;
			ver = 0;
			while (z < ft_strlen(row))
			{

				while (row[z] != ',')
				{
					left[l++] = row[z++];
				}
				while (row[z] != '>' && z < ft_strlen(row))
				{
					right[r++] = row[z++];
				}
				//printf("Left: %d | Right: %d\n", ft_atoi(left) - 400, ft_atoi(right));

				if (hor == ft_atoi(left) - 400)
				{
					//down
					while (ver < ft_atoi(right))
					{
						map[ver++].text[hor] = '#';
					}
					//up
					while (ver > ft_atoi(right))
					{
						map[ver--].text[hor] = '#';
					}
				}
				else if (ver == ft_atoi(right))
				{
					//left
					while (hor > ft_atoi(left) - 400)
					{
						map[ver].text[hor--] = '#';
					}
					//right
					while (hor < ft_atoi(left) - 400)
					{
						map[ver].text[hor++] = '#';
					}
				}

				hor = ft_atoi(left) - 400;
				ver = ft_atoi(right);
				map[ft_atoi(right)].text[ft_atoi(left) - 400] = '#';
				reset_temp(left, &l);
				reset_temp(right, &r);
			}
			reset(row, &i);
		}
	}
	//logic
	counter = 1;
	while (sand.y < 190)
	{
		sand.x = 100;
		sand.y = 1;
		map[sand.y].text[sand.x] = 'o';
		movable = 1;
		while (movable)
		{
			map[sand.y].text[sand.x] = '.';
			if (map[sand.y + 1].text[sand.x] == '.' && sand.y < 190)
				sand.y++;
			else if (map[sand.y + 1].text[sand.x - 1] == '.' && sand.y < 190)
			{
				sand.y++;
				sand.x--;
			}
			else if (map[sand.y + 1].text[sand.x + 1] == '.' && sand.y < 190)
			{
				sand.y++;
				sand.x++;
			}
			else
			{
				movable = 0;
				printf("Sand%d: %d|%d\n", counter, sand.y, sand.x);
				counter++;
			}
			map[sand.y].text[sand.x] = 'o';
		}
	}


	printf("\n\n\n");
	y = 0;
	while (y < 200)
	{
		printf("%s :%d\n", map[y].text, y);
		y++;
	}
	printf("\n\n\n");
	close(input_file);
	return (1);
}
