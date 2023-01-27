/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nroth <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:30:10 by nroth             #+#    #+#             */
/*   Updated: 2022/10/30 14:30:11 by nroth            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINE_H
# define LINE_H

struct s_line
{
	char	*text;
};
typedef struct s_line	line;

#endif

#ifndef VALVE_H
# define VALVE_H

struct s_valve
{
	char	*name;
	char	*leads;
	int		id;
	int		flow;
	int		state;
};
typedef struct s_valve	valve;

#endif

#ifndef PATH_H
# define PATH_H

struct s_path
{
	char	*name;
	char	*leads;
	int		id;
	int		tt;
	int		flow;
	int		state;
	int		score;
};
typedef struct s_path	path;

#endif

