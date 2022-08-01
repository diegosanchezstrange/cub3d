/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ 
/*   Created: 2022/07/23 18:31:29 by dsanchez          #+#    #+#             */ 
/*   Updated: 2022/08/01 21:09:55 by dsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>
#include <mlx.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_hooks_press(int keycode, t_cub *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		free(vars->mlx);
		exit(0);
		return (1);
	}
	if (keycode == KEY_RIGHT)
		vars->keys.RIGHT = 1;
	else if (keycode == KEY_LEFT)
		vars->keys.LEFT = 1;
	else if (keycode == KEY_UP)
		vars->keys.W = 1;
	else if (keycode == KEY_DOWN)
		vars->keys.S = 1;
	//ft_start(vars);
	return (0);
}
int	ft_hooks_release(int keycode, t_cub *vars)
{
	if (keycode == KEY_RIGHT)
		vars->keys.RIGHT = 0;
	else if (keycode == KEY_LEFT)
		vars->keys.LEFT = 0;
	else if (keycode == KEY_UP)
		vars->keys.W = 0;
	else if (keycode == KEY_DOWN)
		vars->keys.S = 0;
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	prog;
	int		i;
	char *str;

	i = 0;
	str = calloc(0, sizeof(char));
	free(str);
	free(str);
	if (argc != 2)
		return (1);
	prog.map = ft_calloc(1, sizeof(char *));
	prog.map[0] = NULL;
	prog.map_w = 0;
	prog.map_h = 0;
	prog.starting_way = 0;
	prog.pos.y = 0;
	prog.pos.x = 0;
	prog.pos.x = 0;
	prog.keys.W = 0;
	prog.keys.A = 0;
	prog.keys.S = 0;
	prog.keys.D = 0;
	prog.keys.LEFT = 0;
	prog.keys.RIGHT = 0;
	if (!ft_parse_file(argv[1], &prog))
		return (2);
	while (prog.map[i])
		ft_printf("|%s|\n", prog.map[i++]);
	ft_printf("%d\n", prog.map_w);
	ft_printf("%d\n", prog.map_h);
	printf("%f\n",prog.pos.x);
	printf("%f\n",prog.pos.y);
	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, WIDTH, HEIGHT, "cub3d");

	mlx_hook(prog.win, 2, 1L << 0, ft_hooks_press, &prog);
	mlx_hook(prog.win, 3, 1L << 1, ft_hooks_release, &prog);

	prog.img.img = mlx_new_image(prog.mlx, WIDTH, HEIGHT);
	prog.img.addr = mlx_get_data_addr(prog.img.img, &(prog.img.bits_per_pixel),
			&(prog.img.line_length), &(prog.img.endian));
	initialize_pos(&prog);
	//ft_start(&prog);
	mlx_loop_hook(prog.mlx, ft_start, &prog);
	mlx_loop(prog.mlx);
	return (0);
}
