/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: johmatos <johmatos@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:49:49 by johmatos          #+#    #+#             */
/*   Updated: 2023/11/09 20:11:55 by johmatos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include <pthread.h>

static void			*thread_routine(void *task);
static int			get_start_idx(int thread_number);
static int			get_end_idx(int thread_number);
static void			draw_pixel(t_task task, int idx);

void	render(t_world world)
{
	int			idx;
	pthread_t	worker[NUM_THREADS];
	t_task		task[NUM_THREADS];

	idx = 0;
	while (idx < NUM_THREADS)
	{
		task[idx] = (t_task){
			.image = world.image,
			.camera = world.camera,
			.world = &world,
			.start_idx = get_start_idx(idx + 1),
			.end_idx = get_end_idx(idx + 1),
		};
		pthread_create(&worker[idx], NULL, thread_routine, &task[idx]);
		idx++;
	}
	idx = -1;
	while (++idx < NUM_THREADS)
		pthread_join(worker[idx], NULL);
}

static inline void	*thread_routine(void *task_ptr)
{
	const t_task	task = *(t_task *)task_ptr;
	int				idx;

	idx = task.start_idx;
	while (idx < task.end_idx)
	{
		draw_pixel(task, idx);
		idx++;
	}
	return (NULL);
}

static inline void	draw_pixel(t_task task, int idx)
{
	const int		x = idx % task.camera.hsize;
	const int		y = idx / task.camera.hsize;
	const t_ray		ray = ray_for_pixel(task.camera, x, y);
	const t_tuple	color = color_at(task.world, &ray);

	mlx_put_pixel(task.image, x, y, normalized_color_to_int(color));
}

static inline int	get_start_idx(int thread_number)
{
	uint	map_size;
	int		remainder;

	if (1 == thread_number)
		return (0);
	map_size = SIZEH * SIZEW;
	remainder = map_size % NUM_THREADS;
	return ((map_size / NUM_THREADS) * (thread_number - 1) + remainder);
}

static inline int	get_end_idx(int thread_number)
{
	uint	map_size;
	short	remainder;

	map_size = SIZEH * SIZEW;
	remainder = map_size % NUM_THREADS;
	return ((map_size / NUM_THREADS) * thread_number + remainder);
}
