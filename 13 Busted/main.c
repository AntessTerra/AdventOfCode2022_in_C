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
		while (++i < 300)
			row[i] = 0;
	}
}

int	main(void)
{
	int		input_file;
	int		i;
	int		z;
	int		x;
	int		y;
	int		*depth;
	int		l;
	int		nl;
	int		r;
	int		nr;
	int		counter;
	int		sum;
	int		correct;
	char	c;
	char	row[300];
	list	*left;
	list	*right;

	i = 0;
	counter = 1;
	sum = 0;
	reset(row, &i);
	input_file = open("input.py", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
		{
			row[++i] = c;
		}
		else
		{
			if (counter % 3 == 1)
			{
				//printf("%s\n",row);
				l = 0;
				nl = 0;
				while(l < ft_strlen(row))
				{
					if (row[l] == '[')
					{
						nl++;
					}
					l++;
				}
				left = malloc(sizeof(list) * nl);
				l = 0;
				while (l < nl)
				{
					left[l++].items = malloc(ft_strlen(row));
				}
				l = 1;
				y = 0;
				x = 0;
				z = 0;
				depth = malloc(sizeof(int) * nl);
				while (l < ft_strlen(row) - 1)
				{

					if (row[l] == ',')
					{
						left[depth[y]].items[++x] = ',';
						x++;
					}
					if (row[l] >= '0' && row[l] <= '9')
					{
						if (row[l] == '1' && row[l + 1] == '0')
						{
							left[depth[y]].items[x] = ':';
							l++;
						}
						else
							left[depth[y]].items[x] = row[l];
					}
					if (row[l] == '[')
					{
						z++;
						left[depth[y]].items[x] = 'l';
						left[depth[y]].items[x + 1] = z + 48;
						x = 0;
						depth[++y] = z;
					}
					if (row[l] == ']')
					{
						y--;
						x = ft_strlen(left[depth[y]].items+1);
					}
					l++;
				}
			}
			if (counter % 3 == 2)
			{
				r = 0;
				nr = 0;
				while(r < ft_strlen(row))
				{
					if (row[r] == '[')
					{
						nr++;
					}
					r++;
				}
				right = malloc(sizeof(list) * nr);
				r = 0;
				while (r < nr)
				{
					right[r++].items = malloc(ft_strlen(row));
				}
				r = 1;
				y = 0;
				x = 0;
				z = 0;
				depth = malloc(sizeof(int) * nl);
				while (r < ft_strlen(row) - 1)
				{
					if (row[r] == ',')
					{
						right[depth[y]].items[++x] = ',';
						x++;
					}
					if (row[r] >= '0' && row[r] <= '9')
					{
						if (row[r] == '1' && row[r + 1] == '0')
						{
							right[depth[y]].items[x] = ':';
							r++;
						}
						else
							right[depth[y]].items[x] = row[r];
					}
					if (row[r] == '[')
					{
						z++;
						right[depth[y]].items[x] = 'l';
						right[depth[y]].items[x + 1] = (0 + z) + 48;
						x = 0;
						depth[++y] = z;
					}
					if (row[r] == ']')
					{
						y--;
						x = ft_strlen(right[depth[y]].items+1);
					}
					r++;
				}
			}

			if (counter % 3 == 0)
			{
				//logic

				correct = 1;
					r = 0;
					while (r < nr)
					{
						x = 0;
						while (x < ft_strlen(right[r].items))
						{
							if (right[r].items[x] >= '0' && right[r].items[x] <= ':')
							{
								if (left[r].items[x] >= '0' && left[r].items[x] <= ':')
								{
									if (right[r].items[x] < left[r].items[x])
									{
										correct = 0;
										break;
									}
									if (right[r].items[x] > left[r].items[x])
										break;
									x++;
								}
							}
							if (right[r].items[x] == 'l')
							if (right[r].items[x] == ',')
								x++;
						}

					}
				//printf("Sum%d: %d\n", counter/3, sum);
				printf("%d---------------------------\n",counter/3);
				y = 0;
				while (y < nl)
				{
					printf("LEFT%d: %s\n", y, left[y].items);
					y++;
				}
				y = 0;
				while (y < nr)
				{
					printf("RIGHT%d: %s\n", y, right[y].items);
					y++;
				}
			}
			counter++;
			reset(row, &i);
		}
	}
	//printf("TotalSum: %d\n", sum);
	close(input_file);
	return (1);
}
