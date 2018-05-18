/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rTv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:10:26 by dhorvill          #+#    #+#             */
/*   Updated: 2018/05/14 00:11:28 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"
#include <stdio.h>

t_coord	detect_collition_plane(t_plane plane, t_coord ray)
{
	t_coord	result;
	double	r1;

	printf("plane.dec: %f\n", plane.dec);
	r1 = plane.dec / (ray.x + ray.y + ray.z);
	result.x = ray.x * r1;
	result.y = ray.y * r1;
	result.z = ray.z * r1;
	return (result);
}

t_coord	get_plane(t_coord a, t_coord b, t_coord c, t_coord ray)
{
	t_coord	ab;
	t_coord	ac;
	t_plane result;
	t_coord	actual_result;

	ab.x = b.x - a.x;
	ab.y = b.y - a.y;
	ab.z = b.z - a.z;
	ac.x = c.x - a.x;
	ac.y = c.y - a.y;
	ac.z = c.z - a.z;
	result.x = (ab.y * ac.z) - (ac.y * ab.z);
	result.y = (ac.x * ab.z) - (ab.x * ac.z);
	result.z = (ab.x * ac.y) - (ac.x * ab.y);
	result.dec = ((result.x * (a.x * -1)) + (result.y * (a.y * -1)) + (result.z * (a.z * -1)));
	actual_result = detect_collition_plane(result, ray);
	return (actual_result);
}

t_coord	detect_collition_sphere(t_coord ray, t_coord center, float radius)
{
	double	delta;
	double	r1;
	double	a;
	double	b;
	double	c;
	t_coord	result;

	a = (pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2)) ;
	b = -(2 * (ray.x * center.x + ray.y * center.y + ray.z * center.z));
	c = (-pow(radius, 2) + pow(center.x, 2) + pow(center.y, 2) + pow(center.z, 2));
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		r1 = (-b - sqrt(delta)) / (2 * a) < (-b + sqrt(delta)) / (2 * a) ?
			(-b - sqrt(delta)) / (2 * a) : (-b + sqrt(delta)) / (2 * a);	
		if (r1 <= 1)		//in sphere or sphere behind and  unity of dstance is camera-screen
		{
			result.x = 0;
			result.y = 0;
			result.z = 0;
			return (result);
		}
		else
		{
			result.x = r1 * ray.x;
			result.y = r1 * ray.y;
			result.z = r1 * ray.z;
			return (result);
		}
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
}

int		touches_light(t_coord center, float radius, t_coord start, t_coord spot)
{
	double	delta;
	double	a;
	double	b;
	double	c;
	double	r1;
	double	r2;
	double  d;
	t_coord	ray;

	ray.z = (spot.z - start.z);
	ray.x = (spot.x - start.x);
	ray.y = (spot.y - start.y);
	d = sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z);
	ray.x /= d;
	ray.y /= d;
	ray.z /= d;
	a = (pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2));
	b = 2 * ((ray.x * start.x - ray.x * center.x) + (ray.y * start.y - ray.y * center.y) + (ray.z * start.z - ray.z * center.z));
	c = pow(start.x, 2) - 2 * start.x * center.x + pow(center.x, 2) + pow(start.y, 2) - 2 * start.y * center.y + pow(center.y, 2) + pow(start.z, 2) - 2 * start.z * center.z + pow(center.z, 2) - pow(radius, 2);
	delta = (b * b) - (4 * a * c);
	if (delta > 0)
	{
		r1 = (-b - sqrt(delta)) / (2 * a);
		r2 = (-b + sqrt(delta)) / (2 * a);
		r1 = fabs(r1) < fabs(r2) ? 0 : r1;
		r2 = fabs(r2) < fabs(r1) ? 0 : r2;
		if (r1 < 0 || r2 < 0)
			return (1);
		if (r1 > 0 || r2 > 0)
			return (0);
	}
	if (delta == 0)
		return (1);
	else
		return (100);
}

int	ft_lum(t_coord center, t_coord start, t_coord spot)
{
	t_coord	ray;
	t_coord ray_spot;
	t_coord	ray_s;
	double	d;
	double	scal;

	ray_spot.x = spot.x - start.x;
	ray_spot.y = spot.y - start.y;
	ray_spot.z = spot.z - start.z;
	d = sqrt(ray_spot.x * ray_spot.x + ray_spot.y * ray_spot.y + ray_spot.z * ray_spot.z);
	ray_spot.x /= d;
	ray_spot.y /= d;
	ray_spot.z /= d;
	ray.x = start.x - center.x;
	ray.y = start.y - center.y;
	ray.z = start.z - center.z;
	d = sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z);
	ray.x /= d;
	ray.y /= d;
	ray.z /= d;
	ray_s.x = ray.x + ray_spot.x;
	ray_s.y = ray.y + ray_spot.y;
	ray_s.z = ray.z + ray_spot.z;
	d = sqrt(pow(ray_s.x, 2) + pow(ray_s.y, 2) + pow(ray_s.z, 2));
	scal = 0.5 * (pow(d, 2) - 2);
	scal = acos(scal);
	scal *= (180 / M_PI);
	return (round(255 - (scal * 255 / 90)) * pow(16, 4));
}

void	raytracer(t_window window, t_coord center, float radius, t_coord spot)
{
	int x;
	int y;
	double d;
	t_coord ray;
	t_coord result;

	y = -1;
	ray.z = 1;
	while (++y < 1000)
	{
		x = -1;
		while (++x < 1000)
		{
			ray.x = (-0.5 + x * 0.001);
			ray.y = (0.5 - y * 0.001);
			d = sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z);
			ray.x /= d;
			ray.y /= d;
			ray.z /= d;
			result = detect_collition_sphere(ray, center, radius);
			if (result.x == 0 && result.y == 0 && result.z == 0)
				window.img_string[x + y * 1000] = 0x000000;
			else if (touches_light(center, radius, result, spot) == 1)
				window.img_string[x + y * 1000] = ft_lum(center, result, spot);
			else if (touches_light(center, radius, result, spot) == 0)
				window.img_string[x + y * 1000] = 0x000000;
			else
				window.img_string[x + y * 1000] = 0x00FF00;
		}
	}
	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
}


int	main(void)
{

	t_coord center;
	t_coord spot;
	t_window	window;
	double radius;

	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, 1000, 1000, "RTv1");
	window.img = mlx_new_image(window.mlx, 1000, 1000);
	window.img_string = (int*)mlx_get_data_addr(window.img, &(window.bpp), &(window.s_l), &(window.endian));
	radius = 1;
	center.x = 0;
	center.y = 0;
	center.z = 5;
	spot.x = 2;
	spot.y = 2;
	spot.z = 0;
	raytracer(window, center, radius, spot);
	t_coord tester1;
	t_coord tester2;
	t_coord tester3;
	t_coord tester4;
	t_coord tester5;

	tester1.x = 0;
	tester1.y = -1;
	tester1.z = 0;
	tester2.x = 1;
	tester2.y = -1;
	tester2.z = 0;
	tester3.x = 0;
	tester3.y = -1;
	tester3.z = 1;
	tester4.x = 0;
	tester4.y = -1;
	tester4.z = 0.5;
	tester5 = get_plane(tester1, tester2, tester3, tester4);
	printf("%f, %f, %f\n", tester5.x, tester5.y, tester5.z);
	mlx_loop(window.mlx);
	return (0);
}
