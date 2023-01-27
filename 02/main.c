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

int	get_score(char elf, char me)
{
	int	score;

	score = 0;
	if (elf == 'A')
	{
		if (me == 'X')
			score = 4;
		if (me == 'Y')
			score = 8;
		if (me == 'Z')
			score = 3;
	}
	if (elf == 'B')
	{
		if (me == 'X')
			score = 1;
		if (me == 'Y')
			score = 5;
		if (me == 'Z')
			score = 9;
	}
	if (elf == 'C')
	{
		if (me == 'X')
			score = 7;
		if (me == 'Y')
			score = 2;
		if (me == 'Z')
			score = 6;
	}
	return	(score);
}

int	get_score2(char elf, char me)
{
	int	score;

	score = 0;
	if (elf == 'A')
	{
		if (me == 'X')
			score = 3;
		if (me == 'Y')
			score = 4;
		if (me == 'Z')
			score = 8;
	}
	if (elf == 'B')
	{
		if (me == 'X')
			score = 1;
		if (me == 'Y')
			score = 5;
		if (me == 'Z')
			score = 9;
	}
	if (elf == 'C')
	{
		if (me == 'X')
			score = 2;
		if (me == 'Y')
			score = 6;
		if (me == 'Z')
			score = 7;
	}
	return	(score);
}

int	main(void)
{
	int		input_file;
	int		i;
	int		sum;
	char	c;
	char	elf;
	char	me;

	i = 1;
	elf = 'A';
	me = 'A';
	sum = 0;
	input_file = open("input", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if ((i % 4) == 1)
			elf = c;
		else if ((i % 4) == 3)
			me = c;
		else if (c == '\n')
		{
			sum = sum + get_score2(elf, me);
			//printf("Score: %d | elf: %c me: %c \n", get_score(elf, me), elf, me);
		}
		i++;
	}
	printf("Score: %d", sum);
	close(input_file);
	return (1);
}
