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

#ifndef POINT_H
# define POINT_H

struct s_point
{
	int		x;
	int		y;
};
typedef struct s_point	point;

#endif

#ifndef HASH_H
# define HASH_H

struct s_hash
{
	point	*p;
	int		nhash;
};
typedef struct s_hash	hash;

#endif



