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

#ifndef MONKEY_H
# define MONKEY_H

struct s_monkey
{
	int	number;
	long	*items;
	int	nitems;
	int	divis;
	int	right;
	int	wrong;
	int	add;
	int	adder;
	int	ninspected;
};
typedef struct s_monkey	monkey;

#endif
