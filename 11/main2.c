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

long	ft_atoi(const char *str)
{
	int	i;
	long	base;
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

void	resetnum(char *row, int *counter)
{
	int	i;

	i = -1;
	if (counter)
		*counter = -1;
	if (row)
	{
		while (++i < 5)
			row[i] = 0;
	}
}

int	main(void)
{
	int		input_file;
	int		i;
	int		n;
	int		j;
	int		k;
	int		counter;
	int		m;
	int		z;
	int		x;
	long	inspect;
	char	c;
	char	row[100];
	char	num[5];
	monkey	*monks;

	i = 0;
	n = 0;
	counter = 1;
	monks = malloc(sizeof(monkey) * 8);
	m = 0;
	while (m < 8)
		monks[m++].items = malloc(sizeof(long) * 100);
	m = 0;
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
			//number
			if (counter % 7 == 1)
				monks[m].number = ft_atoi(row);
			//items
			if (counter % 7 == 2)
			{
				z = (ft_strlen(row) - 16) / 4;
				resetnum(num, &n);
				if (z > 1)
				{
					j = 16;
					x = 0;
					while (x < z)
					{
						k = 0;
						while (k < 4)
						{
							num[k++] = row[j++];
						}
						monks[m].items[x++] = ft_atoi(num);
						resetnum(num, &n);
					}
				}
				else
				{
					x = 0;
					while (x < z)
					{
						monks[m].items[x++] = ft_atoi(row);
					}
				}
				monks[m].nitems = z;
			}
			//operation
			if (counter % 7 == 3)
			{
				if (row[23] == '+')
					monks[m].add = 1;
				if (row[23] == '*')
					monks[m].add = 0;
				if (row[25] == 'o')
					monks[m].adder = 0;
				else
					monks[m].adder = ft_atoi(row);
			}
			//divisible
			if (counter % 7 == 4)
				monks[m].divis = ft_atoi(row);
			if (counter % 7 == 5)
				monks[m].right = ft_atoi(row);
			if (counter % 7 == 6)
				monks[m].wrong = ft_atoi(row);
			if (counter % 7 == 0)
			{
				monks[m].ninspected = 0;
				m++;
			}
			counter++;
			reset(row, &i);
		}
	}
	//Print data
	/*
	m = 0;
	while (m < 4)
	{
		printf("Monkey %d:\n", monks[m].number);
		z = 0;
		printf("Items: ");
		while (z < monks[m].nitems)
		{
			printf("%d ", monks[m].items[z++]);
		}
		printf("\nOperation: new = old %d %d\n", monks[m].add, monks[m].adder);
		printf("Divisible by %d\n", monks[m].divis);
		printf("If True: to monkey%d | If False: to monkey%d\n\n", monks[m].right, monks[m].wrong);
		m++;
	}
	*/
	counter = 0;
	while (counter < 10000)
	{
		m = 0;
		while (m < 8)
		{
			z = 0;
			k = monks[m].nitems;
			while (z < k)
			{
				inspect = monks[m].items[0];
				if (monks[m].add == 1)
					inspect = inspect + monks[m].adder;
				else if (monks[m].add == 0)
				{
					if (monks[m].adder == 0)
					{
						inspect = inspect * inspect;
					}
					else
						inspect = inspect * monks[m].adder;
				}
				inspect = inspect % 9699690;
				//printf("Item: %d | Inspect: %d\n", monks[m].items[0], inspect);
				//right
				if (inspect % monks[m].divis == 0)
				{
					monks[monks[m].right].items[monks[monks[m].right].nitems] = inspect;
					monks[monks[m].right].nitems++;
					j = 0;
					while (j < monks[m].nitems)
					{
						monks[m].items[j] = monks[m].items[j + 1];
						j++;
					}
					monks[m].nitems--;
				}
				//wrong
				else
				{
					monks[monks[m].wrong].items[monks[monks[m].wrong].nitems] = inspect;
					monks[monks[m].wrong].nitems++;
					j = 0;
					while (j < monks[m].nitems)
					{
						monks[m].items[j] = monks[m].items[j + 1];
						j++;
					}
					monks[m].nitems--;
				}
				monks[m].ninspected++;
				z++;
			}
			m++;
		}

		m = 0;
		printf("ROUND %d:\n", counter);
		while (m < 8)
		{

			printf("Monkey %d: ", monks[m].number);
			z = 0;
			while (z < monks[m].nitems)
			{
				printf("%ld ", monks[m].items[z++]);
			}
			printf("\n");
			m++;
		}
		counter++;
	}
	m = 0;
	printf("\n");
	while (m < 8)
	{
		printf("Monkey %d: %d\n", m, monks[m].ninspected);
		m++;
	}
	close(input_file);
	return (1);
}
