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

int		get_priority(char c)
{
	if (c > '[')
		return (c - '`');
	else
		return (c - '&');
}

//Part 1
/*

int		split(char *line, int *counter, int lenght)
{
	int		i;
	int		x;
	int		sum;
	int		check;
	char	first[100];
	char	second[100];

	i = 0;
	sum = 0;
	check = 1;
	reset(first, counter);
	reset(second, counter);
	while (i <= lenght/2)
	{
		first[i] = line[i];
		i++;
	}
	x = 0;
	while (x <= lenght/2)
	{
		second[x++] = line[i++];
	}
	//printf("First half: %s | Second half: %s | Line: %s \n", first, second, line);
	i = 0;
	while (first[i] != '\0')
	{
		x = 0;
		while (second[x] != '\0')
		{
			if (first[i] == second[x] && check)
			{
				sum = sum + get_priority(first[i]);
				//printf("Char: %c | sum: %d \n", first[i], sum);
				check = 0;
			}
			x++;
		}
		i++;
	}
	return (sum);
}


int	main(void)
{
	int		input_file;
	int		i;
	int		sum;
	char	line[100];
	char	c;

	i = 0;
	sum = 0;
	reset(line, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			line[++i] = c;
		else
		{
			sum = sum + split(line, &i, i);
			reset(line, &i);
		}
	}
	printf("OUTPUT: %d\n", sum);
	close(input_file);
	return (1);
}
*/

//Part 2

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

int		group(char *line, char *line2, char *line3)
{
	int		i;
	int		x;
	int		z;

	i = 0;
	while (line[i] != '\0')
	{
		x = 0;
		while (line2[x] != '\0')
		{
			z = 0;
			while (line3[z] != '\0')
			{
				if (line[i] == line2[x] && line[i] == line3[z])
				{
					printf("Char: %c | Priority: %d\n", line[i], get_priority(line[i]));
					return (get_priority(line[i]));
				}
				z++;
			}
			x++;
		}
		i++;
	}

	return (0);
}

int	main(void)
{
	int		input_file;
	int		i;
	int		sum;
	int		counter;
	char	line[100];
	char	line2[100];
	char	line3[100];
	char	c;

	i = 0;
	counter = 1;
	sum = 0;
	reset(line, &i);
	reset(line2, &i);
	reset(line3, &i);
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			line3[++i] = c;
		else if (counter == 1)
		{
			ft_strcpy(line, line3);
			reset(line3, &i);
			counter++;
		}
		else if (counter == 2)
		{
			ft_strcpy(line2, line3);
			reset(line3, &i);
			counter++;
		}
		else
		{
			sum = sum + group(line, line2, line3);
			//printf("Line: %s\nLine2: %s\nLine3: %s\n\n", line, line2, line3);
			reset(line, &i);
			reset(line2, &i);
			reset(line3, &i);
			counter = 1;
		}
	}
	printf("OUTPUT: %d\n", sum);
	close(input_file);
	return (1);
}
