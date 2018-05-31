/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rTv1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 16:10:26 by dhorvill          #+#    #+#             */
/*   Updated: 2018/05/31 12:16:08 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rTv.h"
#include <stdio.h>

t_result detect_collition_cyllinder(t_cyllinder cyllinder, t_coord ray)
{
	double a;
	double b;
	double c;
	double delta;
	double r1;
	t_result result;

	result.figure = 'C';
	a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2) - (pow(cyllinder.norm.x * ray.x, 2) + pow(cyllinder.norm.y * ray.y, 2) + pow(cyllinder.norm.z * ray.z, 2) +
			2 * (cyllinder.norm.x * ray.x * cyllinder.norm.y * ray.y + cyllinder.norm.x * ray.x * cyllinder.norm.z * ray.z + cyllinder.norm.y * ray.y * cyllinder.norm.z * ray.z)) / (pow(cyllinder.norm.x, 2) + pow(cyllinder.norm.y, 2) + pow(cyllinder.norm.z, 2));
	b = -2 * (ray.x * cyllinder.center.x + ray.y * cyllinder.center.y + ray.z * cyllinder.center.z) - (-2 * (pow(cyllinder.norm.x, 2) * ray.x * cyllinder.center.x + pow(cyllinder.norm.y, 2) *
				ray.y * cyllinder.center.y + pow(cyllinder.norm.z, 2) * ray.z * cyllinder.center.z + cyllinder.norm.x * cyllinder.norm.y * ray.x * cyllinder.center.y + cyllinder.norm.x * cyllinder.norm.z * ray.x * cyllinder.center.z + cyllinder.norm.x *
				cyllinder.norm.y * ray.y * cyllinder.center.x + cyllinder.norm.x * cyllinder.norm.z * ray.z * cyllinder.center.x + cyllinder.norm.y * cyllinder.norm.z * ray.y * cyllinder.center.z + cyllinder.norm.y * cyllinder.norm.z * ray.z * cyllinder.center.y)) / (pow(cyllinder.norm.x, 2) + pow(cyllinder.norm.y, 2) + pow(cyllinder.norm.z, 2));
	c = -pow(cyllinder.radius, 2) + pow(cyllinder.center.x, 2) + pow(cyllinder.center.y, 2) + pow(cyllinder.center.z, 2) - (pow(cyllinder.norm.x * cyllinder.center.x, 2) + pow(cyllinder.norm.y * cyllinder.center.y, 2) + pow(cyllinder.norm.z * cyllinder.center.z, 2) + 2 *
			(cyllinder.norm.x * cyllinder.center.x * cyllinder.norm.y * cyllinder.center.y + cyllinder.norm.x * cyllinder.center.x * cyllinder.norm.z * cyllinder.center.z + cyllinder.norm.y * cyllinder.center.y * cyllinder.norm.z * cyllinder.center.z)) / (pow(cyllinder.norm.x, 2) + pow(cyllinder.norm.y, 2) + pow(cyllinder.norm.z, 2));
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		r1 = (-b - sqrt(delta)) / (2 * a) < (-b + sqrt(delta)) / (2 * a) ?
			(-b - sqrt(delta)) / (2 * a) : (-b + sqrt(delta)) / (2 * a);
		if (r1 < 0)
		{
			result.x = 0;
			result.y = 0;
			result.z = 0;
			return (result);
		}
		result.x = ray.x * r1;
		result.y = ray.y * r1;
		result.z = ray.z * r1;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	if (result.x != 0 || result.y != 0 || result.z != 0)
	{
		ray.x = result.x - cyllinder.center.x;
		ray.y = result.y - cyllinder.center.y;
		ray.z = result.z - cyllinder.center.z;
	}
	if (sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z) > sqrt(cyllinder.radius * cyllinder.radius + (cyllinder.height / 2) * (cyllinder.height / 2)))
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}

t_coord detect_collition_egg(t_coord norm, t_coord ray, t_coord ray0, double radius)
{
	double a;
	double b;
	double c;
	double delta;
	double r1;
	t_coord result;

	/*	a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2) + (pow(ray.x * norm.x, 2) + pow(ray.y * norm.y, 2) + pow(norm.z * ray.z, 2) +
		2 * (norm.x * norm.y * ray.x * ray.y + norm.y * norm.z * ray.x * ray.z + norm.y * norm.z * ray.y * ray.z)) / (pow(norm.x, 2)
		+ pow(norm.y, 2) + pow(norm.z, 2));
		b = 0;
		c = -pow(radius, 2);*/
	a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2) + (pow(norm.x * ray.x, 2) + pow(norm.y * ray.y, 2) + pow(norm.z * ray.z, 2) + 2 * (norm.x * ray.x * norm.y * ray.y + norm.x * ray.x * norm.z * ray.z 
				+ norm.y * ray.y * norm.z * ray.z)) / (pow(norm.x, 2) + pow(norm.y, 2) + pow(norm.z, 2));
	b = -2 * (ray.x * ray0.x + ray.y * ray0.y + ray.z * ray0.z) + (-2 * (pow(norm.x, 2) * ray.x * ray0.x + pow(norm.y, 2) * ray.y * ray0.y + pow(norm.z, 2) * ray.z * ray0.z + norm.x * norm.y * ray.x * ray0.y 
				+ norm.x * norm.z * ray.x * ray0.z + norm.x * norm.y * ray.y * ray0.x + norm.x * norm.z * ray.z * ray0.x + norm.y * norm.z * ray.y * ray0.z + norm.y * norm.z * ray.z * ray0.y)) /
		(pow(norm.x, 2) + pow(norm.y, 2) + pow(norm.z, 2));
	c = -pow(radius, 2) + pow(ray0.x, 2) + pow(ray0.y, 2) + pow(ray0.z, 2) + (pow(norm.x * ray0.x, 2) + pow(norm.y * ray0.y, 2) + pow(norm.z * ray0.z, 2) + 2 *
			(norm.x * ray0.x * norm.y * ray0.y + norm.x * ray0.x * norm.z * ray0.z + norm.y * ray0.y * norm.z * ray0.z)) / (pow(norm.x, 2) + pow(norm.y, 2) + pow(norm.z, 2));
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		r1 = (-b - sqrt(delta)) / (2 * a) < (-b + sqrt(delta)) / (2 * a) ?
			(-b - sqrt(delta)) / (2 * a) : (-b + sqrt(delta)) / (2 * a);
		result.x = ray.x * r1;
		result.y = ray.y * r1;
		result.z = ray.z * r1;
	}
	else
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}

t_result detect_collition_cone(double angle, t_coord ray, t_coord center)
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	delta;
	double	r1;
	t_result result;

	result.figure = 'c';
	d = tan((angle * (M_PI / 180)));
	a = pow(ray.x, 2) + pow(ray.y, 2) - pow(ray.z, 2) * d;
	b = 2 * (center.x * ray.x + center.y * ray.y - center.z * ray.z * d);
	c = pow(center.x, 2) + pow(center.y, 2) - pow(center.z, 2) * d;
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		r1 = (-b - sqrt(delta)) / (2 * a) < (-b + sqrt(delta)) / (2 * a) ?
			(-b - sqrt(delta)) / (2 * a) : (-b + sqrt(delta)) / (2 * a);
		if (r1 <= 1)
		{
			result.x = 0;
			result.y = 0;
			result.z = 0;
			return (result);
		}
		result.x = ray.x * r1;
		result.y = ray.y * r1;
		result.z = ray.z * r1;
		return (result);
	}
	result.x = 0;
	result.y = 0;
	result.z = 0;
	return (result);
}

t_result	detect_collition_sphere(t_coord ray, t_sphere sphere)
{
	double	delta;
	double	r1;
	double	a;
	double	b;
	double	c;
	t_result	result;

	a = (pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2)) ;
	b = -(2 * (ray.x * sphere.center.x + ray.y * sphere.center.y + ray.z * sphere.center.z));
	c = (-pow(sphere.radius, 2) + pow(sphere.center.x, 2) + pow(sphere.center.y, 2) + pow(sphere.center.z, 2));
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
			result.figure = 'S';
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

t_result	detect_collition_plane(t_coord ray, t_plane plane)
{
	double		d;
	double		r1;
	double		div;
	t_result	result;

	d = sqrt(pow(plane.norm.x, 2) + pow(plane.norm.y, 2) + pow(plane.norm.z, 2));
	plane.norm.x /= d;
	plane.norm.y /= d;
	plane.norm.z /= d;
	if ((div = ray.x * plane.norm.x + ray.y * plane.norm.y + ray.z * plane.norm.z) == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	r1 = (plane.point.x * plane.norm.x + plane.point.y * plane.norm.y + plane.point.z * plane.norm.z) / div;
	if (r1 <= 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	result.figure = 'P';
	result.x = r1 * ray.x;
	result.y = r1 * ray.y;
	result.z = r1 * ray.z;
	return (result);
}

t_result	detect_collition_disc(t_coord ray, t_disc disc)
{
	double		d;
	double		r1;
	double		div;
	t_coord		dist;
	t_result	result;

	d = sqrt(pow(disc.norm.x, 2) + pow(disc.norm.y, 2) + pow(disc.norm.z, 2));
	disc.norm.x /= d;
	disc.norm.y /= d;
	disc.norm.z /= d;
	if ((div = ray.x * disc.norm.x + ray.y * disc.norm.y + ray.z * disc.norm.z) == 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	r1 = (disc.center.x * disc.norm.x + disc.center.y * disc.norm.y + disc.center.z * disc.norm.z) / div;
	if (r1 <= 0)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
		return (result);
	}
	result.figure = 'D';
	result.x = r1 * ray.x;
	result.y = r1 * ray.y;
	result.z = r1 * ray.z;
	dist.x = result.x - disc.center.x;
	dist.y = result.y - disc.center.y;
	dist.z = result.z - disc.center.z;
	div = (sqrt(pow(dist.x, 2) + pow(dist.y, 2) + pow(dist.z, 2)));
	if (div > disc.radius)
	{
		result.x = 0;
		result.y = 0;
		result.z = 0;
	}
	return (result);
}

int	detect_shadow_plane(t_coord ray, t_plane plane, t_coord spot)
{
	double		d;
	double		r1;
	double		div;
	t_coord		result;

	d = sqrt(pow(plane.norm.x, 2) + pow(plane.norm.y, 2) + pow(plane.norm.z, 2));
	plane.norm.x /= d;
	plane.norm.y /= d;
	plane.norm.z /= d;
	if ((div = ray.x * plane.norm.x + ray.y * plane.norm.y + ray.z * plane.norm.z) == 0)
		return (0);
	r1 = (plane.point.x * plane.norm.x + plane.point.y * plane.norm.y + plane.point.z * plane.norm.z) / div;
	if (r1 <= 0)
		return (0);
	result.x = r1 * ray.x;
	result.y = r1 * ray.y;
	result.z = r1 * ray.z;
	if (pow(spot.x, 2) + pow(spot.y, 2) + pow(spot.z, 2) > pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2))
		return (1);
	else
		return (0);
}

int detect_shadow_disc(t_coord ray, t_disc disc, t_coord spot)
{
	double		d;
	double		r1;
	double		div;
	t_coord		dist;
	t_coord		result;

	d = sqrt(pow(disc.norm.x, 2) + pow(disc.norm.y, 2) + pow(disc.norm.z, 2));
	disc.norm.x /= d;
	disc.norm.y /= d;
	disc.norm.z /= d;
	if ((div = ray.x * disc.norm.x + ray.y * disc.norm.y + ray.z * disc.norm.z) == 0)
		return (0);
	r1 = (disc.center.x * disc.norm.x + disc.center.y * disc.norm.y + disc.center.z * disc.norm.z) / div;
	if (r1 <= 0)
		return (0);
	result.x = r1 * ray.x;
	result.y = r1 * ray.y;
	result.z = r1 * ray.z;
	dist.x = result.x - disc.center.x;
	dist.y = result.y - disc.center.y;
	dist.z = result.z - disc.center.z;
	div = sqrt(pow(dist.x, 2) + pow(dist.y, 2) + pow(dist.z, 2));
	if (div > disc.radius)
		return (0);
	if (pow(spot.x, 2) + pow(spot.y, 2) + pow(spot.z, 2) > pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2))
		return (1);
	else
		return (0);
}

int	detect_shadow_sphere(t_coord ray, t_sphere sphere, t_coord spot)
{
	double	delta;
	double	a;
	double	b;
	t_coord	point;
	double	c;
	double r1;

	a = (pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2)) ;
	b = -(2 * (ray.x * sphere.center.x + ray.y * sphere.center.y + ray.z * sphere.center.z));
	c = (-pow(sphere.radius, 2) + pow(sphere.center.x, 2) + pow(sphere.center.y, 2) + pow(sphere.center.z, 2));
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		r1 = (-b - sqrt(delta)) / (2 * a) < (-b + sqrt(delta)) / (2 * a) ?
			(-b - sqrt(delta)) / (2 * a) : (-b + sqrt(delta)) / (2 * a);
		point.x = ray.x * r1;
		point.y = ray.y * r1;
		point.z = ray.z * r1;
		if (r1 <= 0)
			return (0);
		else if (pow(point.x, 2) + pow(point.y, 2) + pow(point.z, 2) > (pow(spot.x, 2) + pow(spot.y, 2) + pow(spot.z, 2)))
			return (0);
		else
			return (1);
	}
	else
		return (0);
}

int detect_shadow_cyllinder(t_cyllinder cyllinder, t_coord ray, t_coord spot)
{
	double		a;
	double		b;
	double		c;
	int			f;
	double		delta;
	double		r1;
	t_result	result;

	f = 0;
	a = pow(ray.x, 2) + pow(ray.y, 2) + pow(ray.z, 2) - (pow(cyllinder.norm.x * ray.x, 2) + pow(cyllinder.norm.y * ray.y, 2) + pow(cyllinder.norm.z * ray.z, 2) +
			2 * (cyllinder.norm.x * ray.x * cyllinder.norm.y * ray.y + cyllinder.norm.x * ray.x * cyllinder.norm.z * ray.z + cyllinder.norm.y * ray.y * cyllinder.norm.z * ray.z)) / (pow(cyllinder.norm.x, 2) + pow(cyllinder.norm.y, 2) + pow(cyllinder.norm.z, 2));
	b = -2 * (ray.x * cyllinder.center.x + ray.y * cyllinder.center.y + ray.z * cyllinder.center.z) - (-2 * (pow(cyllinder.norm.x, 2) * ray.x * cyllinder.center.x + pow(cyllinder.norm.y, 2) *
				ray.y * cyllinder.center.y + pow(cyllinder.norm.z, 2) * ray.z * cyllinder.center.z + cyllinder.norm.x * cyllinder.norm.y * ray.x * cyllinder.center.y + cyllinder.norm.x * cyllinder.norm.z * ray.x * cyllinder.center.z + cyllinder.norm.x *
				cyllinder.norm.y * ray.y * cyllinder.center.x + cyllinder.norm.x * cyllinder.norm.z * ray.z * cyllinder.center.x + cyllinder.norm.y * cyllinder.norm.z * ray.y * cyllinder.center.z + cyllinder.norm.y * cyllinder.norm.z * ray.z * cyllinder.center.y)) / (pow(cyllinder.norm.x, 2) + pow(cyllinder.norm.y, 2) + pow(cyllinder.norm.z, 2));
	c = -pow(cyllinder.radius, 2) + pow(cyllinder.center.x, 2) + pow(cyllinder.center.y, 2) + pow(cyllinder.center.z, 2) - (pow(cyllinder.norm.x * cyllinder.center.x, 2) + pow(cyllinder.norm.y * cyllinder.center.y, 2) + pow(cyllinder.norm.z * cyllinder.center.z, 2) + 2 *
			(cyllinder.norm.x * cyllinder.center.x * cyllinder.norm.y * cyllinder.center.y + cyllinder.norm.x * cyllinder.center.x * cyllinder.norm.z * cyllinder.center.z + cyllinder.norm.y * cyllinder.center.y * cyllinder.norm.z * cyllinder.center.z)) / (pow(cyllinder.norm.x, 2) + pow(cyllinder.norm.y, 2) + pow(cyllinder.norm.z, 2));
	delta = pow(b, 2) - 4 * a * c;
	if (delta >= 0)
	{
		r1 = (-b - sqrt(delta)) / (2 * a) < (-b + sqrt(delta)) / (2 * a) ?
			(-b - sqrt(delta)) / (2 * a) : (-b + sqrt(delta)) / (2 * a);
		result.x = ray.x * r1;
		result.y = ray.y * r1;
		result.z = ray.z * r1;
		f = 1;
		if (r1 <= 0)
			f = 0;
	}
	else
		return (0);
	ray.x = result.x - cyllinder.center.x;
	ray.y = result.y - cyllinder.center.y;
	ray.z = result.z - cyllinder.center.z;
	if (sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z) > sqrt(cyllinder.radius * cyllinder.radius + (cyllinder.height / 2) * (cyllinder.height / 2)))
		return (0);
	if (pow(spot.x, 2) + pow(spot.y, 2) + pow(spot.z, 2) < pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2))
		f = 0;
	return (f);
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

int	ft_lum_sphere(t_sphere sphere, t_result start, t_coord spot)
{
	t_coord	ray;
	t_coord ray_spot;
	//t_coord	ray_s;
	double	d;
	double	scal;

	ray_spot.x = spot.x - start.x;
	ray_spot.y = spot.y - start.y;
	ray_spot.z = spot.z - start.z;
	d = sqrt(ray_spot.x * ray_spot.x + ray_spot.y * ray_spot.y + ray_spot.z * ray_spot.z);
	ray_spot.x /= d;
	ray_spot.y /= d;
	ray_spot.z /= d;
	ray.x = start.x - sphere.center.x;
	ray.y = start.y - sphere.center.y;
	ray.z = start.z - sphere.center.z;
	d = sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z);
	ray.x /= d;
	ray.y /= d;
	ray.z /= d;
	scal = ray_spot.x * ray.x + ray_spot.y * ray.y + ray_spot.z * ray.z;
//	scal = acos(scal);
//	scal *= (180 / M_PI);
	/*ray_s.x = ray.x + ray_spot.x;
	ray_s.y = ray.y + ray_spot.y;
	ray_s.z = ray.z + ray_spot.z;
	d = sqrt(pow(ray_s.x, 2) + pow(ray_s.y, 2) + pow(ray_s.z, 2));*/
//	scal = 0.5 * (pow(d, 2) - 2);
	scal = acos(scal);
	scal *= (180 / M_PI);
	if (scal < 90)
		return (round(255 - (scal * 255 / 90)) * pow(16, 4));
	else
		return (0);
}

int	ft_lum_plane(t_plane plane, t_result start, t_coord spot)
{
	t_coord ray_spot;
	double	d;
	double	scal;

	ray_spot.x = spot.x - start.x;
	ray_spot.y = spot.y - start.y;
	ray_spot.z = spot.z - start.z;
	d = sqrt(ray_spot.x * ray_spot.x + ray_spot.y * ray_spot.y + ray_spot.z * ray_spot.z);
	ray_spot.x /= d;
	ray_spot.y /= d;
	ray_spot.z /= d;
	ray_spot.x += plane.norm.x;
	ray_spot.y += plane.norm.y;
	ray_spot.z += plane.norm.z;
	d = sqrt(pow(ray_spot.x, 2) + pow(ray_spot.y, 2) + pow(ray_spot.z, 2));
	scal = 0.5 * (pow(d, 2) - 2);
	scal = acos(scal);
	scal *= (180 / M_PI);
	if (scal < 90)
		return (round(255 - (scal * 255 / 90)) * (pow(16, 2) + pow(16, 4) + 1));
	else
		return (0);
}

int	ft_lum_disc(t_disc disc, t_result start, t_coord spot)
{
	t_coord ray_spot;
	double	d;
	double	scal;

	ray_spot.x = spot.x - start.x;
	ray_spot.y = spot.y - start.y;
	ray_spot.z = spot.z - start.z;
	d = sqrt(ray_spot.x * ray_spot.x + ray_spot.y * ray_spot.y + ray_spot.z * ray_spot.z);
	ray_spot.x /= d;
	ray_spot.y /= d;
	ray_spot.z /= d;
	ray_spot.x += disc.norm.x;
	ray_spot.y += disc.norm.y;
	ray_spot.z += disc.norm.z;
	d = sqrt(pow(ray_spot.x, 2) + pow(ray_spot.y, 2) + pow(ray_spot.z, 2));
	scal = 0.5 * (pow(d, 2) - 2);
	scal = acos(scal);
	scal *= (180 / M_PI);
	if (scal < 90)
		return (round(255 - (scal * 255 / 90)) * pow(16, 2));
	else
		return (0);
}

int ft_lum_cyllinder(t_cyllinder cyllinder, t_result start, t_coord spot)
{
	t_coord	ray_spot;
	t_coord top_start;
	t_coord	ray_s;
	double	d;
	double	p;
	double	dist;
	double	scal;

	d = sqrt(cyllinder.norm.x * cyllinder.norm.x + cyllinder.norm.y * cyllinder.norm.y + cyllinder.norm.z * cyllinder.norm.z);
	cyllinder.norm.x /= d;
	cyllinder.norm.y /= d;
	cyllinder.norm.z /= d;
	cyllinder.norm.x *= (cyllinder.height / 2);
	cyllinder.norm.y *= (cyllinder.height / 2);
	cyllinder.norm.z *= (cyllinder.height / 2);
	ray_spot.x = spot.x - start.x;
	ray_spot.y = spot.y - start.y;
	ray_spot.z = spot.z - start.z;
	d = sqrt(ray_spot.x * ray_spot.x + ray_spot.y * ray_spot.y + ray_spot.z * ray_spot.z);
	ray_spot.x /= d;
	ray_spot.y /= d;
	ray_spot.z /= d;
	top_start.x = start.x - (cyllinder.norm.x + cyllinder.center.x);
	top_start.y = start.y - (cyllinder.norm.y + cyllinder.center.y);
	top_start.z = start.z - (cyllinder.norm.z + cyllinder.center.z);
	dist = sqrt(top_start.x * top_start.x + top_start.y * top_start.y + top_start.z * top_start.z);
	d = (cyllinder.radius * cyllinder.radius) - (dist * dist);
	d *= -1;
	d = sqrt(d);
	p = sqrt(cyllinder.norm.x * cyllinder.norm.x + cyllinder.norm.y * cyllinder.norm.y + cyllinder.norm.z * cyllinder.norm.z);
	cyllinder.norm.x /= p;
	cyllinder.norm.y /= p;
	cyllinder.norm.z /= p;
	p -= d;
	cyllinder.norm.x *= p;
	cyllinder.norm.y *= p;
	cyllinder.norm.z *= p;
	start.x -= cyllinder.norm.x;
	start.y -= cyllinder.norm.y;
	start.z -= cyllinder.norm.z;
	top_start.x = start.x - cyllinder.center.x;
	top_start.y = start.y - cyllinder.center.y;
	top_start.z = start.z - cyllinder.center.z;
	d = sqrt(top_start.x * top_start.x + top_start.y * top_start.y + top_start.z * top_start.z);
	top_start.x /= d;
	top_start.y /= d;
	top_start.z /= d;
	ray_s.x = top_start.x + ray_spot.x;
	ray_s.y = top_start.y + ray_spot.y;
	ray_s.z = top_start.z + ray_spot.z;
	d = sqrt(pow(ray_s.x, 2) + pow(ray_s.y, 2) + pow(ray_s.z, 2));
	scal = 0.5 * (pow(d, 2) - 2);
	scal = acos(scal);
	scal *= (180 / M_PI);
	if (scal < 90)
		return (round(255 - (scal * 255 / 90)) * pow(16, 2));
	else
		return (0);
}

int	ft_check_shadow(t_result result, t_cyllinder *cyllinders, t_sphere *spheres, t_disc *discs, int cyllinder_count, int sphere_count, t_coord spots, int pos, t_plane *planes, int plane_count)
{
	int			i;
	double		d;
	t_coord		ray;
	int			f;
	t_coord 	spot;

	i = -1;
	f = 0;
	spot = spots;
	ray.x = spot.x - result.x;
	ray.y = spot.y - result.y;
	ray.z = spot.z - result.z;
	spot.x = ray.x;
	spot.y = ray.y;
	spot.z = ray.z;
	d = sqrt(pow(ray.x, 2) + pow(ray.y, 2)+ pow(ray.z, 2));
	ray.x /= d;
	ray.y /= d;
	ray.z /= d;
	while (++i < sphere_count)
	{
		if (!(i == pos && result.figure == 'S'))
		{
			spheres[i].center.x -= result.x;
			spheres[i].center.y -= result.y;
			spheres[i].center.z -= result.z;
			if (detect_shadow_sphere(ray, spheres[i], spot) == 1)
			{
				spheres[i].center.x += result.x;
				spheres[i].center.y += result.y;
				spheres[i].center.z += result.z;
				f = 1;
				return (1);
				break ;
			}
			spheres[i].center.x += result.x;
			spheres[i].center.y += result.y;
			spheres[i].center.z += result.z;
		}
	}
	i = -1;
	while (++i < cyllinder_count)
	{	
		if (f == 1)
			break ;
		if (!(i == pos && result.figure == 'C'))
		{
			cyllinders[i].center.x -= result.x;
			cyllinders[i].center.y -= result.y;
			cyllinders[i].center.z -= result.z;
			if (detect_shadow_cyllinder(cyllinders[i], ray, spot) == 1)
			{
				cyllinders[i].center.x += result.x;
				cyllinders[i].center.y += result.y;
				cyllinders[i].center.z += result.z;
				f = 1;
				return (1);
				break;
			}
			cyllinders[i].center.x += result.x;
			cyllinders[i].center.y += result.y;
			cyllinders[i].center.z += result.z;
		}
	}
	i = -1;
	while (++i < cyllinder_count * 2)
	{
		if (f == 1)
			break;
		if (!(i == pos && result.figure == 'D'))
		{
			discs[i].center.x -= result.x;
			discs[i].center.y -= result.y;
			discs[i].center.z -= result.z;
			if (detect_shadow_disc(ray, discs[i], spot) == 1)
			{
				discs[i].center.x += result.x;
				discs[i].center.y += result.y;
				discs[i].center.z += result.z;
				f = 1;
				return (1);
				break;
			}
			discs[i].center.x += result.x;
			discs[i].center.y += result.y;
			discs[i].center.z += result.z;
		}
	}
	i = -1;
	while (++i < plane_count)
	{
		if (f == 1)
			break;
		if (!(i == pos && result.figure == 'P'))
		{
			planes[i].point.x -= result.x;
			planes[i].point.y -= result.y;
			planes[i].point.z -= result.z;
			if (detect_shadow_plane(ray, planes[i], spot) == 1)
			{
				planes[i].point.x += result.x;
				planes[i].point.y += result.y;
				planes[i].point.z += result.z;
				f = 1;
				return (1);
				break;
			}
			planes[i].point.x += result.x;
			planes[i].point.y += result.y;
			planes[i].point.z += result.z;
		}
	}
	return (f);
}

void	raytracer(t_window window, t_objects objects)
{
	int x;
	int y;
	int i;
	int flag;
	int place_holder;
	double d;
	int shadow;
	t_coord ray;
	t_result	result;
	t_result	tmp;

	y = -1;
	ray.z = 1;
	while (++y < 1000)
	{
		x = -1;
		while (++x < 1000)
		{
			shadow = 10;
			result.x = 0;
			result.y = 0;
			result.z = 0;
			flag = 0;
			result.figure = 'a';
			ray.x = (-0.5 + x * 0.001);
			ray.y = (0.5 - y * 0.001);
			d = sqrt(ray.x * ray.x + ray.y * ray.y + ray.z * ray.z);
			ray.x /= d;
			ray.y /= d;
			ray.z /= d;
			i = -1;
			while (++i < objects.sphere_count)
			{
				tmp = detect_collition_sphere(ray, objects.spheres[i]);
				if (tmp.x != 0 || tmp.y != 0 || tmp.z != 0)
				{
					if (pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2) < pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2) || flag == 0)
					{
						flag = 1;
						result = tmp;
						place_holder = i;
					}
				}
			}
			i = -1;
			while (++i < objects.cyllinder_count)
			{
				tmp = detect_collition_cyllinder(objects.cyllinders[i], ray);
				if (tmp.x != 0 || tmp.y != 0 || tmp.z != 0)
				{
					if (pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2) < pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2)|| flag == 0)
					{
						flag = 1;
						result = tmp;
						place_holder = i;
					}
				}
			}
			i = -1;
			while (++i < objects.cyllinder_count * 2)
			{	
				d = sqrt(pow(objects.discs[i].norm.x, 2) + pow(objects.discs[i].norm.y, 2) + pow(objects.discs[i].norm.z, 2));
				objects.discs[i].norm.x /= d;
				objects.discs[i].norm.y /= d;
				objects.discs[i].norm.z /= d;
				if (sqrt(pow(objects.discs[i].center.x + objects.discs[i].norm.x, 2) + pow(objects.discs[i].center.y + objects.discs[i].norm.y, 2) + pow(objects.discs[i].center.z + objects.discs[i].norm.z, 2)) >
						sqrt(pow(objects.discs[i].center.x - objects.discs[i].norm.x, 2) + pow(objects.discs[i].center.y - objects.discs[i].norm.y, 2) + pow(objects.discs[i].center.z - objects.discs[i].norm.z, 2)))
				{
					objects.discs[i].norm.x *= -1;
					objects.discs[i].norm.y *= -1;
					objects.discs[i].norm.z *= -1;
				}
				tmp = detect_collition_disc(ray, objects.discs[i]);
				if (tmp.x != 0 || tmp.y != 0 || tmp.z != 0)
				{
					if (pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2) < pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2)|| flag == 0)
					{
						flag = 1;
						result = tmp;
						place_holder = i;
					}
				}
			}
			i = -1;
			while (++i < objects.plane_count)
			{	
				d = sqrt(pow(objects.planes[i].norm.x, 2) + pow(objects.planes[i].norm.y, 2) + pow(objects.planes[i].norm.z, 2));
				objects.planes[i].norm.x /= d;
				objects.planes[i].norm.y /= d;
				objects.planes[i].norm.z /= d;
				if (sqrt(pow(objects.planes[i].point.x + objects.planes[i].norm.x, 2) + pow(objects.planes[i].point.y + objects.planes[i].norm.y, 2) + pow(objects.planes[i].point.z + objects.planes[i].norm.z, 2)) >
						sqrt(pow(objects.planes[i].point.x - objects.planes[i].norm.x, 2) + pow(objects.planes[i].point.y - objects.planes[i].norm.y, 2) + pow(objects.planes[i].point.z - objects.planes[i].norm.z, 2)))
				{
					objects.planes[i].norm.x *= -1;
					objects.planes[i].norm.y *= -1;
					objects.planes[i].norm.z *= -1;
				}
				tmp = detect_collition_plane(ray, objects.planes[i]);
				if (tmp.x != 0 || tmp.y != 0 || tmp.z != 0)
				{
					if (pow(tmp.x, 2) + pow(tmp.y, 2) + pow(tmp.z, 2) < pow(result.x, 2) + pow(result.y, 2) + pow(result.z, 2) || flag == 0)
					{
						flag = 1;
						result = tmp;
						place_holder = i;
					}
				}
			}
			if (result.x != 0 || result.y != 0 || result.z != 0)
				shadow = ft_check_shadow(result, objects.cyllinders, objects.spheres, objects.discs, objects.cyllinder_count, objects.sphere_count, objects.spot, place_holder, objects.planes, objects.plane_count);
			if ((result.x == 0 && result.y == 0 && result.z == 0) || shadow == 1)
				window.img_string[x + y * 1000] = 0x000000;
			else if (result.figure =='C')
				window.img_string[x + y * 1000] = ft_lum_cyllinder(objects.cyllinders[place_holder], result, objects.spot);
			else if (result.figure == 'S')
				window.img_string[x + y * 1000] = ft_lum_sphere(objects.spheres[place_holder], result, objects.spot);
			else if (result.figure == 'P')
				window.img_string[x + y * 1000] = ft_lum_plane(objects.planes[place_holder], result, objects.spot);
			else if (result.figure == 'D')
				window.img_string[x + y * 1000] = ft_lum_disc(objects.discs[place_holder], result, objects.spot);
			else if (result.figure == 'c')
				window.img_string[x + y * 1000] = 0xFF0000;
		}
	}
	mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
}


int	main(int argc, char **argv)
{
	int		arguments;
	int		i;
	int		j;
	int		k;
	int		kd;
	int		l;
	int		camera;
	double	standard;
	t_coord	standarized;
	t_objects	objects;

	objects.sphere_count = 0;
	objects.cyllinder_count = 0;
	objects.plane_count = 0;
	j = -1;
	k = -1;
	camera = 0;
	kd = -2;
	l = -1;
	objects.matrix.x1 = 1;
	objects.matrix.y1 = 0;
	objects.matrix.z1 = 0;
	objects.matrix.x2 = 0;
	objects.matrix.y2 = 1;
	objects.matrix.z2 = 0;
	objects.matrix.x3 = 0;
	objects.matrix.y3 = 0;
	objects.matrix.z3 = 1;
	arguments = 4;
	if (argc < 2)
		return (0);
	i = -1;
	while (argv[++i])
	{
		if (ft_strcmp(argv[i],"Sphere") == 0)
		{
			arguments += 5;
			objects.sphere_count++;
		}
		else if (ft_strcmp(argv[i], "Cyllinder") == 0)
		{
			objects.cyllinder_count++;
			arguments += 9;
		}
		else if (ft_strcmp(argv[i], "Plane") == 0)
		{
			objects.plane_count++;
			arguments += 7;
		}
		else if (ft_strcmp(argv[i], "Camera") == 0)
			arguments += 6;
	}
	if (argc != arguments)
	{	
		ft_putnbr(arguments);
		ft_putchar('\n');
		ft_putnbr(argc);
		ft_putendl("exits bad");
		return (0);
	}
	if ((objects.spheres = (t_sphere*)malloc(sizeof(objects.spheres) * (objects.sphere_count + 100))) == 0)
		return (0);
	if ((objects.cyllinders = (t_cyllinder*)malloc(sizeof(objects.cyllinders) * (objects.cyllinder_count + 100))) == 0)
		return (0);
	if ((objects.planes = (t_plane*)malloc(sizeof(objects.planes) * (objects.plane_count + 100))) == 0)
		return (0);
	if ((objects.discs = (t_disc*)malloc(sizeof(objects.cyllinders) * (objects.cyllinder_count * 2 + 100))) == 0)
		return (0);
	i = -1;																		//URGENT: DO AN ATOF FUNCTION!!!
	objects.spot.x = atof(argv[1]);
	objects.spot.y = atof(argv[2]);
	objects.spot.z = atof(argv[3]);
	objects.spoti = objects.spot;
	while (argv[++i])
	{
		if (ft_strcmp(argv[i], "Sphere") == 0)
		{
			j++;
			objects.spheres[j].center.x = atof(argv[i + 1]);
			objects.spheres[j].center.y = atof(argv[i + 2]);
			objects.spheres[j].center.z = atof(argv[i + 3]);
			objects.spheres[j].centeri = objects.spheres[j].center;
			objects.spheres[j].radius = atof(argv[i + 4]);
		}
		else if (ft_strcmp(argv[i], "Cyllinder") == 0)
		{
			k++;
			kd += 2;
			objects.cyllinders[k].center.x = atof(argv[i + 1]);
			objects.cyllinders[k].center.y = atof(argv[i + 2]);
			objects.cyllinders[k].center.z = atof(argv[i + 3]);
			objects.cyllinders[k].norm.x = atof(argv[i + 4]);
			objects.cyllinders[k].norm.y = atof(argv[i + 5]);
			objects.cyllinders[k].norm.z = atof(argv[i + 6]);
			objects.cyllinders[k].radius = atof(argv[i + 7]);
			objects.cyllinders[k].height = atof(argv[i + 8]);
			standard = sqrt(pow(objects.cyllinders[k].norm.x, 2) + pow(objects.cyllinders[k].norm.y, 2) + pow(objects.cyllinders[k].norm.z, 2));
			standarized.x = objects.cyllinders[k].norm.x / standard;
			standarized.y = objects.cyllinders[k].norm.y / standard;
			standarized.z = objects.cyllinders[k].norm.z / standard;
			objects.discs[kd].radius = objects.cyllinders[k].radius;
			objects.discs[kd + 1].radius = objects.discs[kd].radius;
			objects.discs[kd].norm.x = objects.cyllinders[k].norm.x;
			objects.discs[kd].norm.y = objects.cyllinders[k].norm.y;
			objects.discs[kd].norm.z = objects.cyllinders[k].norm.z;
			objects.discs[kd + 1].norm.x = objects.cyllinders[k].norm.x;
			objects.discs[kd + 1].norm.y = objects.cyllinders[k].norm.y;
			objects.discs[kd + 1].norm.z = objects.cyllinders[k].norm.z;
			objects.discs[kd].center.x = objects.cyllinders[k].center.x + (standarized.x * (objects.cyllinders[k].height / 2));
			objects.discs[kd].center.y = objects.cyllinders[k].center.y + (standarized.y * (objects.cyllinders[k].height / 2));
			objects.discs[kd].center.z = objects.cyllinders[k].center.z + (standarized.z * (objects.cyllinders[k].height / 2));
			objects.discs[kd + 1].center.x = objects.cyllinders[k].center.x - (standarized.x * (objects.cyllinders[k].height / 2));
			objects.discs[kd + 1].center.y = objects.cyllinders[k].center.y - (standarized.y * (objects.cyllinders[k].height / 2));
			objects.discs[kd + 1].center.z = objects.cyllinders[k].center.z - (standarized.z * (objects.cyllinders[k].height / 2));
			objects.cyllinders[k].centeri = objects.cyllinders[k].center;
			objects.cyllinders[k].normi = objects.cyllinders[k].norm;
			objects.discs[kd].centeri = objects.discs[kd].center;
			objects.discs[kd + 1].centeri = objects.discs[kd + 1].center;
			objects.discs[kd].normi = objects.discs[kd].norm;
			objects.discs[kd + 1].normi = objects.discs[kd + 1].norm;
		}
		else if (ft_strcmp(argv[i], "Plane") == 0)
		{
			l++;
			objects.planes[l].point.x = atof(argv[i + 1]);
			objects.planes[l].point.y = atof(argv[i + 2]);
			objects.planes[l].point.z = atof(argv[i + 3]);
			objects.planes[l].norm.x = atof(argv[i + 4]);
			objects.planes[l].norm.y = atof(argv[i + 5]);
			objects.planes[l].norm.z = atof(argv[i + 6]);
			objects.planes[l].pointi = objects.planes[l].point;
			objects.planes[l].normi = objects.planes[l].norm;
		}
		else if (ft_strcmp(argv[i], "Camera") == 0)
		{
			if (camera == 1)
			{
				ft_putendl("Please assign a single camera.");
				return (0);
			}
			camera = 1;
			objects.camera.pos.x = atof(argv[i + 1]);
			objects.camera.pos.y = atof(argv[i + 2]);
			objects.camera.pos.z = atof(argv[i + 3]);
			objects.camera.rot.x = atof(argv[i + 4]);
			objects.camera.rot.y = atof(argv[i + 5]);
		}
	}
	if (camera == 1)
	{
		change_pos_init(&objects);
		rotate_matrix_init(&objects);
	}
	objects.window.mlx = mlx_init();
	objects.window.win = mlx_new_window(objects.window.mlx, 1000, 1000, "RTv1");
	objects.window.img = mlx_new_image(objects.window.mlx, 1000, 1000);
	objects.window.img_string = (int*)mlx_get_data_addr(objects.window.img, &(objects.window.bpp), &(objects.window.s_l), &(objects.window.endian));
	raytracer(objects.window, objects);
	mlx_key_hook(objects.window.win, interactive, (void *)&objects);
	mlx_loop(objects.window.mlx);
	return (0);
}
