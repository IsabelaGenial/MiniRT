/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 04:33:58 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/11/19 04:34:05 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	intersect_cylinder(void **obj, t_tuple obj_dist_to_ray, t_ray r)
{
	t_intersection	xs;
	float			a;

	(void)obj, (void)obj_dist_to_ray;
	ft_bzero((void *)&xs, sizeof(t_intersection));
	a = (pow(r.direction[X], 2) + pow(r.direction[Z], 2));
	if (floats_eq(0, a))
		return (xs);
	else
		xs.count = 42;
	return (xs);
}
