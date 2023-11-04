/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_with_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:39:02 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/11/03 15:51:58 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_intersection	intersect_world_with_ray(t_world *w, t_ray *r)
{
	t_intersection		obj1_intersects;
	t_intersection		obj2_intersects;
	const t_sphere		*s1 = &w->objs[0];
	const t_sphere		*s2 = &w->objs[1];

	obj1_intersects = create_intersection(s1, *r);
	obj2_intersects = create_intersection(s2, *r);
	obj1_intersects = link_intersection_nodes((t_node *[]){
			intersection(obj1_intersects.head->t, s1),
			intersection(obj2_intersects.head->t, s2),
			intersection(obj2_intersects.head->next->t, s2),
			intersection(obj1_intersects.head->next->t, s1),
			NULL \
	});
	return (obj1_intersects);
}
