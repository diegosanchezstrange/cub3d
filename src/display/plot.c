/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclerico <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 20:12:18 by mclerico          #+#    #+#             */
/*   Updated: 2022/08/04 20:16:56 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <stdio.h>

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= WIDTH || y >= HEIGHT || y < 0 || x < 0)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel_color(t_data *data, int x, int y)
{
	char	*dst;
	int		color;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

int	ft_bigger(double x, double y)
{
	if (x < y)
		return (1);
	return (-1);
}

int	get_fromrgb(int rgb[3])
{
	if (!rgb)
		return (0);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	vertical_line(double x, double yi, double yo, t_cub params)
{
	int	s;
	int	color;

	s = ft_bigger(yi, yo);
	if (yi == 0)
		color = get_fromrgb(params.C_color);
	else
		color = get_fromrgb(params.F_color);
	while (yi != yo)
	{
		my_mlx_pixel_put(&(params.img), x, yi, color);
		yi += s;
	}
}
/*
void	plot_line(t_point p1, t_point p2, t_data img, t_data tex)
{
	t_point	s;
	t_point	d;
	double	err[2];
	int		color;
	t_point	p0;

	//printf("%f, %f\n", p1.y, p2.y);
	s = (t_point){ft_bigger(p1.x, p2.x), ft_bigger(p1.y, p2.y), 0, 0};
	d = (t_point){ft_abs(p2.x - p1.x), ft_abs(p2.y - p1.y) * -1, 0, 0};
	//printf("%f, %f\n", d.x, d.y);
	err[0] = d.x + d.y;
	//printf("error: %f\n",err[0]);
	p0 = p1;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		//printf("traza plot\n");
		color = get_pixel_color(&tex, tex.texX, tex.texY);
		my_mlx_pixel_put(&img, p1.x, p1.y, color);
//		printf("error: %f\n",err[0]);
		err[1] = 2 * err[0];
		if (err[1] >= d.y)
		{
			err[0] += d.y;
			p1.x += s.x;
		}
		if (err[1] <= d.x)
		{
			err[0] += d.x;
			p1.y += s.y;
		}
	}
}
*/
