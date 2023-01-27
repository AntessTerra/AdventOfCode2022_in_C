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

void	reset(char *line, int *counter)
{
	int	i;

	i = -1;
	if (counter)
		*counter = -1;
	if (line)
	{
		while (++i < 100)
			line[i] = 0;
	}
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	main(void)
{
	//Part 1
	/*
	int		input_file;
	int		i;
	char	c;
	char	x;
	char	y;
	char	z;

	i = 0;
	z = 0;
	y = 0;
	x = 0;
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (i == 0)
		{
			z = c;
			i++;
		}
		else if (i == 1)
		{
			y = c;
			i++;
		}
		else if (i == 2)
		{
			x = c;
			i++;
		}
		else
		{
			if (z != y && z != x && z != c && y != x && y != c && x != c)
				printf("Marker start: %d %c|%c|%c|%c\n", i, z, y, x, c);
			z = y;
			y = x;
			x = c;
			i++;
		}
	}
	close(input_file);
	return (1);
	*/
	//Part 2
		int		input_file;
	int		i;
	int		x;
	int		z;
	int		mess;
	char	c;
	char	line[10000];

	i = 0;
	reset(line, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		mess = 1;
		if (i < 13)
			line[++i] = c;
		else
		{
			//check
			x = i - 12;
			while (x < i)
			{
				z = x + 1;
				while (z < i + 1)
				{
					if (line[x] == line[z])
						mess = 0;
					z++;
				}
				x++;
			}
			if (mess)
				printf("Message: %d Line: %s\n", i, line);
			line[++i] = c;
		}
	}
	//printf("Line: %s", line);
	close(input_file);
	return (1);
}
