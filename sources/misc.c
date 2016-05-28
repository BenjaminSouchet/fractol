/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 13:09:02 by bsouchet          #+#    #+#             */
/*   Updated: 2016/05/27 14:10:15 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		rotate_fractal(t_var *v)
{
	int		rot;

	rot = v->rot;
	if (rot >= 0)
		while (rot >= 360)
			rot -= 360;
	else
		while (rot < -0)
			rot += 360;
	if (rot == 0 && (v->e = 0) == 0)
		while (v->z < 0)
			v->z = v->z * -1;
	else if (rot == 90 && (v->e = 1) == 1)
		while (v->z < 0)
			v->z = v->z * -1;
	else if (rot == 180 && (v->e = 2) == 2)
		while (v->z > 0)
			v->z = v->z * -1;
	else if (rot == 270 && (v->e = 3) == 3)
		while (v->z > 0)
			v->z = v->z * -1;
	v->minx = (((WIN_W + v->padx) / 2) / (v->z / 2)) / -2;
	v->miny = (((WIN_H + v->pady) / 2) / (v->z / 2)) / -2;
}

void			fractal_julia(t_var *v)
{
	v->i = -1.0;
	v->cr = -1.1380;
	v->ci = 0.2403;
	rotate_fractal(v);
	v->zr = (v->e == 0 || v->e == 2) ? ((double)v->x / v->z) + v->minx :
		((double)v->y / v->z) + v->miny;
	v->zi = (v->e == 0 || v->e == 2) ? ((double)v->y / v->z) + v->miny :
		((double)v->x / v->z) + v->minx;
	while (++v->i < v->imax && (v->zr * v->zr + v->zi * v->zi) < 4)
	{
		v->tmp = v->zr;
		v->zr = (v->zr * v->zr) - (v->zi * v->zi) + v->cr;
		v->zi = v->mod * v->zi * v->tmp + v->ci;
	}
	v->color = ft_gradient_color(v->color1, v->color2, (v->i / v->imax));
	put_pixel(v, 0);
}

void			fractal_mandelbrot(t_var *v)
{
	v->i = -1.0;
	v->zr = 0.0;
	v->zi = 0.0;
	rotate_fractal(v);
	v->cr = (v->e == 0 || v->e == 2) ? ((double)v->x / v->z) + v->minx : 
		((double)v->y / v->z) + v->miny;
	v->ci = (v->e == 0 || v->e == 2) ? ((double)v->y / v->z) + v->miny :
		((double)v->x / v->z) + v->minx;
	while (++v->i < v->imax && (v->zr * v->zr + v->zi * v->zi) < 4)
	{
		v->tmp = v->zr;
		v->zr = (v->zr * v->zr) - (v->zi * v->zi) + v->cr;
		v->zi = v->mod * v->zi * v->tmp + v->ci;
	}
	v->color = ft_gradient_color(v->color1, v->color2, (v->i / v->imax));
	put_pixel(v, 0);
}
