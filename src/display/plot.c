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

int	ft_bigger(double x, double y)
{
	if (x < y)
		return (1);
	return (-1);
}

void	plot_line(t_point p1, t_point p2, t_data img, int color)
{
	t_point	s;
	t_point	d;
	double		err[2];
	//t_point	p0;

	s = (t_point){ft_bigger(p1.x, p2.x), ft_bigger(p1.y, p2.y), 0, 0};
	d = (t_point){ft_abs(p2.x - p1.x), ft_abs(p2.y - p1.y) * -1, 0, 0};
	err[0] = d.x + d.y;
	//p0 = p1;
	while (p1.x != p2.x || p1.y != p2.y)
	{
		my_mlx_pixel_put(&img, p1.x, p1.y, color);
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
