/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 07:40:28 by dhorvill          #+#    #+#             */
/*   Updated: 2018/05/30 15:21:47 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rTv.h"

t_objects	*rotate_matrix(t_objects *objects, int keycode)
{
	t_matrix tmp;

	tmp = objects->matrix;
	if (keycode == 86)
	{
		objects->matrix.x1 = tmp.x1 * cos(M_PI / 16) + tmp.x3 * -sin(M_PI / 16);
		objects->matrix.y1 = tmp.y1 * cos(M_PI / 16) + tmp.y3 * -sin(M_PI / 16);
		objects->matrix.z1 = tmp.z1 * cos(M_PI / 16) + tmp.z3 * -sin(M_PI / 16);
		objects->matrix.x3 = tmp.x1 * sin(M_PI / 16) + tmp.x3 * cos(M_PI / 16);
		objects->matrix.y3 = tmp.y1 * sin(M_PI / 16) + tmp.y3 * cos(M_PI / 16);
		objects->matrix.z3 = tmp.z1 * sin(M_PI / 16) + tmp.z3 * cos(M_PI / 16);
	}
	if (keycode == 88)
	{
		objects->matrix.x1 = tmp.x1 * cos(M_PI / 16) + tmp.x3 * sin(M_PI / 16);
		objects->matrix.y1 = tmp.y1 * cos(M_PI / 16) + tmp.y3 * sin(M_PI / 16);
		objects->matrix.z1 = tmp.z1 * cos(M_PI / 16) + tmp.z3 * sin(M_PI / 16);
		objects->matrix.x3 = tmp.x1 * -sin(M_PI / 16) + tmp.x3 * cos(M_PI / 16);
		objects->matrix.y3 = tmp.y1 * -sin(M_PI / 16) + tmp.y3 * cos(M_PI / 16);
		objects->matrix.z3 = tmp.z1 * -sin(M_PI / 16) + tmp.z3 * cos(M_PI / 16);
	}
	if (keycode == 91)
	{
		objects->matrix.x2 = tmp.x2 * cos(M_PI / 16) + tmp.x3 * sin(M_PI / 16);
		objects->matrix.y2 = tmp.y2 * cos(M_PI / 16) + tmp.y3 * sin(M_PI / 16);
		objects->matrix.z2 = tmp.z2 * cos(M_PI / 16) + tmp.z3 * sin(M_PI / 16);
		objects->matrix.x3 = tmp.x2 * -sin(M_PI / 16) + tmp.x3 * cos(M_PI / 16);
		objects->matrix.y3 = tmp.y2 * -sin(M_PI / 16) + tmp.y3 * cos(M_PI / 16);
		objects->matrix.z3 = tmp.z2 * -sin(M_PI / 16) + tmp.z3 * cos(M_PI / 16);
	}
	if (keycode == 87)
	{
		objects->matrix.x2 = tmp.x2 * cos(M_PI / 16) + tmp.x3 * -sin(M_PI / 16);
		objects->matrix.y2 = tmp.y2 * cos(M_PI / 16) + tmp.y3 * -sin(M_PI / 16);
		objects->matrix.z2 = tmp.z2 * cos(M_PI / 16) + tmp.z3 * -sin(M_PI / 16);
		objects->matrix.x3 = tmp.x2 * sin(M_PI / 16) + tmp.x3 * cos(M_PI / 16);
		objects->matrix.y3 = tmp.y2 * sin(M_PI / 16) + tmp.y3 * cos(M_PI / 16);
		objects->matrix.z3 = tmp.z2 * sin(M_PI / 16) + tmp.z3 * cos(M_PI / 16);
	}
		printf("%f, %f, %f\n %f, %f, %f\n %f, %f, %f\n", objects->matrix.x1, objects->matrix.y1, objects->matrix.z1, objects->matrix.x2, objects->matrix.y2, objects->matrix.z2, objects->matrix.x3, objects->matrix.y3, objects->matrix.z3); 
	return (objects);
}

t_objects	*change_sphere_pos(t_objects *objects)
{
	int i;
	t_sphere	sphere;

	i = -1;
	while (++i < objects->sphere_count)
	{
		sphere = objects->spheres[i];
		objects->spheres[i].center.x = sphere.centeri.x * objects->matrix.x1 + sphere.centeri.y * objects->matrix.x2 + sphere.centeri.z * objects->matrix.x3;
		objects->spheres[i].center.y = sphere.centeri.x * objects->matrix.y1 + sphere.centeri.y * objects->matrix.y2 + sphere.centeri.z * objects->matrix.y3;
		objects->spheres[i].center.z = sphere.centeri.x * objects->matrix.z1 + sphere.centeri.y * objects->matrix.z2 + sphere.centeri.z * objects->matrix.z3;
	}
	return (objects);
}

t_objects	*change_plane_pos(t_objects *objects)
{
	int i;
	t_plane	plane;

	i = -1;
	while (++i < objects->plane_count)
	{
		plane = objects->planes[i];
		objects->planes[i].point.x = plane.pointi.x  * objects->matrix.x1 + plane.pointi.y * objects->matrix.x2 + plane.pointi.z * objects->matrix.x3;
		objects->planes[i].point.y = plane.pointi.x  * objects->matrix.y1 + plane.pointi.y * objects->matrix.y2 + plane.pointi.z * objects->matrix.y3;
		objects->planes[i].point.z = plane.pointi.x  * objects->matrix.z1 + plane.pointi.y * objects->matrix.z2 + plane.pointi.z * objects->matrix.z3;
		objects->planes[i].norm.x = plane.normi.x  * objects->matrix.x1 + plane.normi.y * objects->matrix.x2 + plane.normi.z * objects->matrix.x3;
		objects->planes[i].norm.y = plane.normi.x  * objects->matrix.y1 + plane.normi.y * objects->matrix.y2 + plane.normi.z * objects->matrix.y3;
		objects->planes[i].norm.z = plane.normi.x  * objects->matrix.z1 + plane.normi.y * objects->matrix.z2 + plane.normi.z * objects->matrix.z3;
	}
	return (objects);
}

t_objects	*change_cyllinder_pos(t_objects *objects)
{
	int i;
	t_cyllinder cyllinder;

	i = -1;
	while (++i < objects->cyllinder_count)
	{
		cyllinder = objects->cyllinders[i];
		objects->cyllinders[i].center.x = cyllinder.centeri.x * objects->matrix.x1 + cyllinder.centeri.y * objects->matrix.x2 + cyllinder.centeri.z * objects->matrix.x3;
		objects->cyllinders[i].center.y = cyllinder.centeri.x * objects->matrix.y1 + cyllinder.centeri.y * objects->matrix.y2 + cyllinder.centeri.z * objects->matrix.y3;
		objects->cyllinders[i].center.z = cyllinder.centeri.x * objects->matrix.z1 + cyllinder.centeri.y * objects->matrix.z2 + cyllinder.centeri.z * objects->matrix.z3;
		objects->cyllinders[i].norm.x = cyllinder.normi.x * objects->matrix.x1 + cyllinder.normi.y * objects->matrix.x2 + cyllinder.normi.z * objects->matrix.x3;
		objects->cyllinders[i].norm.y = cyllinder.normi.x * objects->matrix.y1 + cyllinder.normi.y * objects->matrix.y2 + cyllinder.normi.z * objects->matrix.y3;
		objects->cyllinders[i].norm.z = cyllinder.normi.x * objects->matrix.z1 + cyllinder.normi.y * objects->matrix.z2 + cyllinder.normi.z * objects->matrix.z3;
	}
	return (objects);	
}

t_objects	*change_disc_pos(t_objects *objects)
{
	int i;
	t_disc disc;

	i = -1;
	while (++i < objects->cyllinder_count * 2)
	{
		disc = objects->discs[i];
		objects->discs[i].center.x = disc.centeri.x * objects->matrix.x1 + disc.centeri.y * objects->matrix.x2 + disc.centeri.z * objects->matrix.x3;
		objects->discs[i].center.y = disc.centeri.x * objects->matrix.y1 + disc.centeri.y * objects->matrix.y2 + disc.centeri.z * objects->matrix.y3;
		objects->discs[i].center.z = disc.centeri.x * objects->matrix.z1 + disc.centeri.y * objects->matrix.z2 + disc.centeri.z * objects->matrix.z3;
		objects->discs[i].norm.x = disc.normi.x * objects->matrix.x1 + disc.normi.y * objects->matrix.x2 + disc.normi.z * objects->matrix.x3;
		objects->discs[i].norm.y = disc.normi.x * objects->matrix.y1 + disc.normi.y * objects->matrix.y2 + disc.normi.z * objects->matrix.y3;
		objects->discs[i].norm.z = disc.normi.x * objects->matrix.z1 + disc.normi.y * objects->matrix.z2 + disc.normi.z * objects->matrix.z3;
	}
	return (objects);	
}

t_objects	*change_spot_pos(t_objects *objects)
{
	t_coord spot;

	spot = objects->spoti;
	objects->spot.x = spot.x * objects->matrix.x1 + spot.y * objects->matrix.x2 + spot.z * objects->matrix.x3; 
	objects->spot.y = spot.x * objects->matrix.y1 + spot.y * objects->matrix.y2 + spot.z * objects->matrix.y3; 
	objects->spot.z = spot.x * objects->matrix.z1 + spot.y * objects->matrix.z2 + spot.z * objects->matrix.z3; 
	return (objects);
}

int	interactive(int	keycode, t_objects *objects)
{
	int i;
	int	pressed;

	ft_putnbr(keycode);
	ft_putchar('\n');
	pressed = 0;
	if (keycode == 53)
		exit(0);
	if (keycode == 13)
	{
		pressed = 1;
		i = -1;
		while (++i < objects->sphere_count)
		{
			objects->spheres[i].center.z -= 0.5;
			objects->spheres[i].centeri.z -= 0.5;
		}
		i = -1;
		while (++i < objects->plane_count)
		{
			objects->planes[i].point.z -= 0.5;
			objects->planes[i].pointi.z -= 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count)
		{
			objects->cyllinders[i].center.z -= 0.5;
			objects->cyllinders[i].centeri.z -= 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count * 2)
		{
			objects->discs[i].center.z -= 0.5;
			objects->discs[i].centeri.z -= 0.5;
		}
		objects->spot.z -= 0.5;
		objects->spoti.z -= 0.5;
	}
	if (keycode == 1)
	{
		pressed = 1;
		i = -1;
		while (++i < objects->sphere_count)
		{
			objects->spheres[i].center.z += 0.5;
			objects->spheres[i].centeri.z += 0.5;
		}
		i = -1;
		while (++i < objects->plane_count)
		{
			objects->planes[i].point.z += 0.5;
			objects->planes[i].pointi.z += 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count)
		{
			objects->cyllinders[i].center.z += 0.5;
			objects->cyllinders[i].centeri.z += 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count * 2)
		{
			objects->discs[i].center.z += 0.5;
			objects->discs[i].centeri.z += 0.5;
		}
		objects->spot.z += 0.5;
		objects->spoti.z += 0.5;
	}
	if (keycode == 0)
	{
		pressed = 1;
		i = -1;
		while (++i < objects->sphere_count)
		{
			objects->spheres[i].center.x += 0.5;
			objects->spheres[i].centeri.x += 0.5;
		}
		i = -1;
		while (++i < objects->plane_count)
		{
			objects->planes[i].point.x += 0.5;
			objects->planes[i].pointi.x += 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count)
		{
			objects->cyllinders[i].center.x += 0.5;
			objects->cyllinders[i].centeri.x += 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count * 2)
		{
			objects->discs[i].center.x += 0.5;
			objects->discs[i].centeri.x += 0.5;
		}
		objects->spot.x += 0.5;
		objects->spoti.x += 0.5;
	}
	if (keycode == 2)
	{
		pressed = 1;
		i = -1;
		while (++i < objects->sphere_count)
		{
			objects->spheres[i].center.x -= 0.5;
			objects->spheres[i].centeri.x -= 0.5;
		}
		i = -1;
		while (++i < objects->plane_count)
		{
			objects->planes[i].point.x -= 0.5;
			objects->planes[i].pointi.x -= 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count)
		{
			objects->cyllinders[i].center.x -= 0.5;
			objects->cyllinders[i].centeri.x -= 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count * 2)
		{
			objects->discs[i].center.x -= 0.5;
			objects->discs[i].centeri.x -= 0.5;
		}
		objects->spot.x -= 0.5;
		objects->spoti.x -= 0.5;
	}
	if (keycode == 49)
	{
		pressed = 1;
		i = -1;
		while (++i < objects->sphere_count)
		{
			objects->spheres[i].center.y -= 0.5;
			objects->spheres[i].centeri.y -= 0.5;
		}
		i = -1;
		while (++i < objects->plane_count)
		{
			objects->planes[i].point.y -= 0.5;
			objects->planes[i].pointi.y -= 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count)
		{
			objects->cyllinders[i].center.y -= 0.5;
			objects->cyllinders[i].centeri.y -= 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count * 2)
		{
			objects->discs[i].center.y -= 0.5;
			objects->discs[i].centeri.y -= 0.5;
		}
		objects->spot.y -= 0.5;
		objects->spoti.y -= 0.5;
	}
	if (keycode == 257)
	{
		pressed = 1;
		i = -1;
		while (++i < objects->sphere_count)
		{
			objects->spheres[i].center.y += 0.5;
			objects->spheres[i].center.y += 0.5;
		}
		i = -1;
		while (++i < objects->plane_count)
		{
			objects->planes[i].point.y += 0.5;
			objects->planes[i].pointi.y += 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count)
		{
			objects->cyllinders[i].center.y += 0.5;
			objects->cyllinders[i].centeri.y += 0.5;
		}
		i = -1;
		while (++i < objects->cyllinder_count * 2)
		{
			objects->discs[i].center.y += 0.5;
			objects->discs[i].centeri.y += 0.5;
		}
		objects->spot.y += 0.5;
		objects->spoti.y += 0.5;
	}
	if (keycode == 88 || keycode == 86 || keycode == 87 || keycode == 91)
	{
		pressed = 1;
		i = -1;
		objects = rotate_matrix(objects, keycode);
		objects = change_sphere_pos(objects);
		objects = change_plane_pos(objects);
		objects = change_cyllinder_pos(objects);
		objects = change_disc_pos(objects);
		objects = change_spot_pos(objects);
	}
	if (keycode == 126)
	{
		pressed = 1;
		objects->spoti.y += 0.5;
		objects->spot.y += 0.5;
	}
	if (keycode == 125)
	{
		pressed = 1;
		objects->spoti.y -= 0.5;
		objects->spot.y -= 0.5;
	}
	if (keycode == 123)
	{
		pressed = 1;
		objects->spoti.x -= 0.5;
		objects->spot.x -= 0.5;
	}
	if (keycode == 124)
	{
		pressed = 1;
		objects->spoti.x += 0.5;
		objects->spot.x += 0.5;
	}
	if (keycode == 116)
	{
		pressed = 1;
		objects->spoti.z += 0.5;
		objects->spot.z += 0.5;
	}
	if (keycode == 121)
	{
		pressed = 1;
		objects->spot.z -= 0.5;
		objects->spoti.z -= 0.5;
	}
	if (pressed == 1)
	{
		mlx_destroy_image(objects->window.mlx, objects->window.img);
		objects->window.img = mlx_new_image(objects->window.mlx, 1000, 1000);
		objects->window.img_string = (int*)mlx_get_data_addr(objects->window.img, &(objects->window.bpp), &(objects->window.s_l), &(objects->window.endian));
		raytracer(objects->window, *objects);
	}
	return (0);
}
