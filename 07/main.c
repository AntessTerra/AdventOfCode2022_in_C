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

int	main(void)
{
	int		input_file;
	int		i;
	int		x;
	int		y;
	int		z;
	int		counter;
	int		ndir;
	int		lenght;
	//int		total_sum;
	char	c;
	char	row[100];
	line	*lines;
	dir		*dirs;

	dirs = malloc(sizeof(dir) * 1000);
	lines = malloc(sizeof(line) * 2000);
	i = 0;
	counter = 0;
	ndir = 0;
	//total_sum = 0;
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
			lines[counter].text = malloc(100);
			ft_strcpy(lines[counter].text, row);
			counter++;
			reset(row, &i);
		}
	}
	x = 0;
	while (x < counter)
	{
		if (lines[x].text[0] == '$' && lines[x].text[1] == ' ' && lines[x].text[2] == 'l' && lines[x].text[3] == 's')
		{
			lenght = ft_strlen(lines[x - 1].text);
			dirs[ndir].name = malloc(100);
			reset(row, &y);
			y = 0;
			while (y + 5 < lenght)
			{
				row[y] = lines[x - 1].text[y + 5];
				y++;
			}
			ft_strcpy(dirs[ndir].name, row);
			reset(row, &y);
			dirs[ndir].nopen = 1;
			z = x + 1;
			while (dirs[ndir].nopen > 0 && z < counter)
			{
				if (lines[z].text[0] >= '0' && lines[z].text[0] <= '9')
					dirs[ndir].size = dirs[ndir].size + ft_atoi(lines[z].text);
				if (lines[z].text[0] == '$' && lines[z].text[2] == 'c' && lines[z].text[5] == '.')
					dirs[ndir].nopen = dirs[ndir].nopen - 1;
				if (lines[z].text[0] == '$' && lines[z].text[2] == 'c' && lines[z].text[5] != '.')
					dirs[ndir].nopen = dirs[ndir].nopen + 1;
				z++;
			}
			ndir++;
		}
		/*
		if (lines[x].text[0] >= '0' && lines[x].text[0] <= '9')
		{
			dirs[ndir - 1].size = dirs[ndir - 1].size + ft_atoi(lines[x].text);
		}
		*/
		x++;
	}
	//Part 1
	/*
	x = 0;
	while (x < ndir)
	{
		if (dirs[x].size <= 100000)
			total_sum = total_sum + dirs[x].size;
		printf("Total sum: %d\n", total_sum);
		x++;
	}
	*/
	//Part 2
	x = 0;
	while (x < ndir)
	{
		if (dirs[x].size >= 6975962)
			printf("Dir%d name: %s | sum: %d\n", x + 1, dirs[x].name, dirs[x].size);
		x++;
	}

	close(input_file);
	return (1);
}
