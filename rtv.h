/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 22:34:03 by dhorvill          #+#    #+#             */
/*   Updated: 2018/05/31 09:47:15 by dhorvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H

# include "libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <fcntl.h>


typedef struct	s_coord
{
	double	x;
	double	y;
	double	z;
}				t_coord;

typedef struct	s_camera
{
	t_coord		pos;
	t_coord		rot;
}				t_camera;

typedef struct	s_matrix
{
	double		x1;
	double		y1;
	double		z1;
	double		x2;
	double		y2;
	double		z2;
	double		x3;
	double		y3;
	double		z3;
}				t_matrix;

typedef struct	s_sphere
{
	t_coord	center;
	t_coord	centeri;
	double	radius;
}				t_sphere;

typedef struct	s_cyllinder
{
	t_coord	center;
	t_coord	norm;
	t_coord centeri;
	t_coord normi;
	double	radius;
	double	height;
}				t_cyllinder;

typedef struct	s_disc
{
	double radius;
	t_coord center;
	t_coord	norm;
	t_coord centeri;
	t_coord normi;
}				t_disc;

typedef struct t_plane
{
	t_coord point;
	t_coord	norm;
	t_coord	pointi;
	t_coord	normi;
}				t_plane;

typedef struct	s_result
{
	double	x;
	double	y;
	double	z;
	char	figure;
	t_plane	plane;
}				t_result;

typedef struct	s_window
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*img_string;
	int		bpp;
	int		endian;
	int		s_l;
}				t_window;

typedef struct	s_objects
{
	t_window	window;
	t_plane		*planes;
	t_sphere	*spheres;
	t_cyllinder	*cyllinders;
	t_disc		*discs;
	t_coord		spot;
	t_coord		spoti;
	t_matrix	matrix;
	t_camera	camera;
	int			plane_count;
	int			cyllinder_count;
	int			sphere_count;
}				t_objects;

int			interactive(int keycode, t_objects *objects);
void		raytracer(t_window window, t_objects objects);
t_objects	*change_pos_init(t_objects *objects);
t_objects	*rotate_matrix_init(t_objects *objects);

#endif
