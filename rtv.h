/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhorvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 22:21:47 by dhorvill          #+#    #+#             */
/*   Updated: 2018/05/13 23:00:53 by dhorvill         ###   ########.fr       */
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

typedef struct	s_plane
{
	double	x;
	double	y;
	double	z;
	double	dec;
}				t_plane;

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

#endif
