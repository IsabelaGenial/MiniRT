/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 17:22:57 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/11/19 17:23:16 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_bonus.h"
#include "minirt.h"

t_intersections	link_intersection_nodes(t_intersection *arr[])
{
	(void)arr;
	return ((t_intersections){0});
}

t_intersection	intersection(double t, t_sphere *obj)
{
	t_intersection	result;

	result.t = t;
	result.object = obj;
	return (result);
}
