/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_material.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 11:26:35 by vcedraz-          #+#    #+#             */
/*   Updated: 2023/10/31 16:13:03 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//t_material	create_material(void)
//{
//	return ((t_material){
//		.color = create_tuple(1, 1, 1, COLOR),
//		.ambient = 0.1,
//		.diffuse = 0.9,
//		.specular = 0.9,
//		.shininess = 200.0
//	});
//}
//
//t_material	create_plane_material(void)
//{
//	return ((t_material){0});
//}

static void    compute_the_specular(t_type_light *c, t_lighting *l);
static void    create_black(t_type_light *c, int single);
static void    init_of_compute(t_type_light *c, t_lighting *l);

t_tuple    calculate_lighting(t_lighting *l)
{
	t_tuple            result;
	t_type_light    c;

	init_of_compute(&c, l);
	c.a = multiply_tuple_by_scalar(c.effective_color, l.material.ambient);
	if(l->in_shadow)
		return (c.a);
	c.light_dot_normal = dot(c.lightv, l->normal_vec);
	if (c.reflect_dot_eye < 0)
		create_black(&c,0);
	else
	{
		c.d = multiply_tuple_by_scalar(c.effective_color, \
                c.light_dot_normal * l->material.diffuse);
		c.lightv = negate_tuple(c.lightv);
		c.reflectv = reflect(c.lightv,l->normal_vec);
		c.reflect_dot_eye = dot(c.reflectv, l->eye_vec);
		if (c.light_dot_normal <= 0)
			create_black(&c,1);
		else
			compute_the_specular(&c, l);
	}
	result = add_three_tuples(c.a, c.d, c.s);
	return (result);
}

static void    init_of_compute(t_type_light *c, t_lighting *l)
{
	c->effective_color = multiply_colors(l->material.color, l->light.intensity);
	c->lightv = subtract_tuples(l->light.position, l->point);
	c->lightv = normalize(c->lightv);

}

static void    create_black(t_type_light *c, int single)
{
	if (!single)
	{
		c->s = create_tuple(0, 0, 0, COLOR);
		c->d = create_tuple(0, 0, 0, COLOR);
	}
	else
		c->s = create_tuple(0, 0, 0, COLOR);
}

static void    compute_the_specular(t_type_light *c, t_lighting *l)
{
	c->factor = pow(c->reflect_dot_eye, l->material.shininess);
	c->s = multiply_tuple_by_scalar(c->d, c->light_dot_normal);
}