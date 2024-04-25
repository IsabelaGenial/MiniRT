/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface_normals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:33:40 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/10/20 11:37:07 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_tuple	sphere_normal_at(const t_shape *sphere, const t_tuple world_point)
{
	t_tuple	object_normal;
	t_tuple	world_normal;
	t_tuple	object_point;

	object_point = multiply_tuple_by_matrix(world_point, sphere->inverse_t);
	object_normal = subtract_tuples(object_point, sphere->origin);
	world_normal = multiply_tuple_by_matrix(object_normal, sphere->trans_inv);
	world_normal.w = VECTOR;
	return (normalize(world_normal));
}

t_tuple	plane_normal_at( \
		const t_shape *plane, const t_tuple world_point)
{
	const t_tuple	up = create_vector(0, 1, 0);
	const t_tuple	new_nrmal = multiply_tuple_by_matrix(up, plane->trans_inv);

	(void)world_point;
	return (normalize(new_nrmal));
}

void	cylinder_normal_at( \
		const t_shape *cyl, const t_tuple world_point, t_tuple res)
{
	(void)cyl;
	(void)world_point;
	(void)res;
}