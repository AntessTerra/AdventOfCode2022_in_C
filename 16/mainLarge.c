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
	while ((str[i] < '0' || str[i] > '9') && str[i] != '-')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
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
		while (i < 100)
			temp[i++] = 0;
	}
}

void	reset_path(path *path, int *counter)
{
	int	i;

	i = 0;
	if (counter)
		*counter = 1;
	if (path)
	{
		while (i < 70)
		{
			path[i].flow = 0;
			path[i].name = 0;
			path[i].leads = 0;
			path[i].state = 0;
			path[i].score = 0;
			path[i].tt = 0;
			path[i].id = 0;
			i++;
		}
	}
}


int	main(void)
{
	int		input_file;
	int		i;
	int		z;
	int		x;
	int		y;
	int		m;
	int		l;
	int		r;
	int		p;
	int		v;
	int		b;
	int		npath;
	int		nreverse;
	int		score;
	int		time;
	int		ttime;
	int		travel;
	int		pout;
	int		sum;
	int		next;
	int		appendable;
	int		now;
	char	c;
	char	row[200];
	char	left[100];
	char	right[100];
	valve	*valves;
	path	*paths;
	path	*reverse;

	valves = malloc(sizeof(valve) * 70);
	paths = malloc(sizeof(path) * 70);
	reverse = malloc(sizeof(path) * 70);
	z = 0;
	while (z < 70)
	{
		valves[z].name = malloc(5);
		valves[z].leads = malloc(70);
		z++;
	}
	i = 0;
	l = 0;
	r = 0;
	v = 0;
	reset(row, &i);
	reset_temp(left, &l);
	reset_temp(right, &r);
	input_file = open("inputLarge", O_RDONLY);
	while (read(input_file, &c, 1))
	{
		if (c != '\n')
			row[++i] = c;
		else
		{
			z = 0;
			while (row[z] != ';')
				left[l++] = row[z++];
			while (z < ft_strlen(row))
				right[r++] = row[z++];
			valves[v].name[0] = left[6];
			valves[v].name[1] = left[7];
			valves[v].flow = ft_atoi(left);
			z = 0;
			x = 0;
			while (z < ft_strlen(right))
			{
				if (right[z] >= 'A' && right[z] <= 'Z')
				{
					valves[v].leads[x++] = right[z++];
					valves[v].leads[x++] = right[z++];
					valves[v].leads[x++] = ',';
				}
				z++;
			}
			valves[v].leads[x] = '\0';
			valves[v].state = 0;
			valves[v].id = v;
			//printf("%s | %s\n", left, right);
			reset_temp(left, &l);
			reset_temp(right, &r);
			reset(row, &i);
			v++;
		}
	}
	//logic
	time = 30;
	sum = 0;
	npath = 1;
	now = 25;
	travel = 0;
	while (time > 0)
	{
		if (travel == 0)
			printf("Now in %s\n", valves[now].name);
		else
			printf("Moving to %s\n", valves[now].name);
		pout = 0;
		paths[0].name = valves[now].name;
		paths[0].flow = valves[now].flow;
		paths[0].leads = valves[now].leads;
		paths[0].state = valves[now].state;
		paths[0].id = valves[now].id;
		paths[0].tt = 0;
		x = 0;
		ttime = 1;
		while (x < npath)
		{

			next = ft_strlen(paths[x].leads) / 3;
			y = 0;
			b = 0;
			while (y < next)
			{
				z = 0;
				while (z < v)
				{
					if (valves[z].name[0] == paths[x].leads[b] && valves[z].name[1] == paths[x].leads[b + 1])
					{
						//printf("Found path to: %s\n", valves[z].name);
						appendable = 1;
						m = 0;
						while (m < npath)
						{
							if (paths[m].name[0] == valves[z].name[0] && paths[m].name[1] == valves[z].name[1])
								appendable = 0;
							m++;
						}
						if (appendable && ttime < time)
						{
							if (valves[z].state == 0)
								score = valves[z].flow * (time - ttime - 1);
							else
								score = 0;
							//printf("Appended: %s | Tt: %d | Score: %d\n", valves[z].name, ttime, score);
							paths[npath].name = valves[z].name;
							paths[npath].flow = valves[z].flow;
							paths[npath].leads = valves[z].leads;
							paths[npath].state = valves[z].state;
							paths[npath].score = score;
							paths[npath].id = valves[z].id;
							paths[npath].tt = ttime;
							npath++;
						}
						b = b + 3;
					}
					z++;
				}
				y++;
			}
			x++;
			ttime = paths[x].tt;
			ttime++;
		}
		//now
		if (travel == 0)
		{
			m = 1;
			if (paths[0].state == 0)
				score = paths[0].flow * (time - paths[0].tt - 1);
			else
				score = 0;
			ttime = paths[0].tt;
			now = paths[0].id;
			printf("BASE: %s | Tt: %d | Score: %d\n", paths[0].name, paths[0].tt, score);
			while (m < npath)
			{
				if (paths[m].score > 0)
					printf("Path%d: %s | Tt: %d | Score: %d\n", paths[m].id, paths[m].name, paths[m].tt, paths[m].score);
				if (paths[m].score > score)
				{
					printf("NEWBASE: %s | Tt: %d | Score: %d | ID: %d\n", paths[m].name, paths[m].tt, paths[m].score, paths[m].id);
					score = paths[m].score;
					ttime = paths[m].tt;
					travel = paths[m].tt;
					now = paths[m].id;
				}
				m++;
			}
		}
		else
			travel--;
		z = 0;
		while (z < v)
		{
			if (valves[z].state == 1)
				pout = pout + valves[z].flow;
			z++;
		}
		sum = sum + pout;
		if (now == paths[0].id && travel == 0)
		{
			valves[paths[0].id].state = 1;
			printf("Turned valve %s open\n", valves[now].name);
		}
		reset_path(paths, &npath);
		printf("Cycle:%d | Pout: %d | Sum: %d\n\n", time - 31, pout, sum);
		time--;
	}

	z = 0;
	while (z < v)
	{
		if (valves[z].flow > 0)
			printf("Valve%d: %s | %d pm | Leads: %s | Open: %d\n", z, valves[z].name, valves[z].flow, valves[z].leads, valves[z].state);
		z++;
	}
	close(input_file);
	return (1);
}
