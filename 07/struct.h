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

#ifndef STRUCT_H
# define STRUCT_H

struct s_item
{
	unsigned int		size;
	int		nopen;
	char	*name;
};
typedef struct s_item	dir;

#endif

#ifndef LINE_H
# define LINE_H

struct s_line
{
	char	*text;
};
typedef struct s_line	line;

#endif
