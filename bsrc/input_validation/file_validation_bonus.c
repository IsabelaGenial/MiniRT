/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcedraz- <vcedraz-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 17:24:25 by vcedraz-          #+#    #+#             */
/*   Updated: 2024/04/14 18:47:35 by vcedraz-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_if_theres_one_of_each_unique_identifier(t_checker *c);

_Bool	file_validation(int fd, int *valid_lines)
{
	t_checker	c;

	c = (t_checker){0};
	c.fd = fd;
	c.line = ft_gnl(fd);
	if (!c.line)
		free_and_exit_error(c.line, NULL, fd);
	while (c.line)
	{
		c.splitted = ft_split(c.line, ' ');
		if (c.line[0] != '\n')
		{
			(*valid_lines)++;
			check_type_identifiers(&c);
			validate_line(c.line, c.splitted, fd);
		}
		free(c.line);
		ft_free_t_split(c.splitted);
		c.line = ft_gnl(fd);
	}
	check_if_theres_one_of_each_unique_identifier(&c);
	return (true);
}

void	free_and_exit_error(char *line, t_split *splitted, int fd)
{
	while (line)
	{
		free(line);
		line = ft_gnl(fd);
	}
	ft_free_t_split(splitted);
	exit(1);
}

static void	check_if_theres_one_of_each_unique_identifier(t_checker *c)
{
	if (3 != (c->counters[AMBIENT] + c->counters[CAMERA] + c->counters[LIGHT]))
	{
		printf(RED
			"Error: you need one Ambient light, one Light and one Camera!\n"
			RESET);
		free_and_exit_error(c->line, NULL, c->fd);
	}
}
