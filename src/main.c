/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 18:31:29 by dsanchez          #+#    #+#             */
/*   Updated: 2022/09/10 19:02:32 by dsanchez         ###   ########.fr       */
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
		ft_free_all(vars);
		exit(0);
		return (1);
	}
	if (keycode == KEY_RIGHT)
		vars->keys.right = 1;
	else if (keycode == KEY_LEFT)
		vars->keys.left = 1;
	else if (keycode == KEY_W)
		vars->keys.w = 1;
	else if (keycode == KEY_S)
		vars->keys.s = 1;
	else if (keycode == KEY_A)
		vars->keys.a = 1;
	else if (keycode == KEY_D)
		vars->keys.d = 1;
	return (0);
}

int	ft_hooks_release(int keycode, t_cub *vars)
{
	if (keycode == KEY_RIGHT)
		vars->keys.right = 0;
	else if (keycode == KEY_LEFT)
		vars->keys.left = 0;
	else if (keycode == KEY_W)
		vars->keys.w = 0;
	else if (keycode == KEY_S)
		vars->keys.s = 0;
	else if (keycode == KEY_A)
		vars->keys.a = 0;
	else if (keycode == KEY_D)
		vars->keys.d = 0;
	return (0);
}

int	ft_init_params(t_cub *prog)
{
	prog->params = ft_calloc(1, sizeof(t_render));
	prog->no_path = NULL;
	prog->so_path = NULL;
	prog->we_path = NULL;
	prog->ea_path = NULL;
	if (!prog->params)
		return (0);
	prog->params->dir.x = 0;
	prog->params->dir.y = -1;
	prog->params->plane.x = 0.66;
	prog->params->plane.y = 0;
	return (1);
}

int	ft_init_prog(t_cub *prog)
{
	prog->map = ft_calloc(1, sizeof(char *));
	if (!prog->map)
		return (0);
	prog->map[0] = NULL;
	prog->map_w = 0;
	prog->map_h = 0;
	prog->starting_way = 0;
	prog->pos.y = 0;
	prog->pos.x = 0;
	prog->keys.w = 0;
	prog->keys.a = 0;
	prog->keys.s = 0;
	prog->keys.d = 0;
	prog->keys.left = 0;
	prog->keys.right = 0;
	return (ft_init_params(prog));
}

int	prog(int argc, char **argv)
{
	t_cub	prog;

	if (argc != 2)
		return (1);
	if (!ft_init_prog(&prog))
		return (1);
	prog.mlx = mlx_init();
	if (!ft_parse_file(argv[1], &prog))
	{
		ft_free_cub(&prog);
		free(prog.mlx);
		return (2);
	}
	prog.win = mlx_new_window(prog.mlx, WIDTH, HEIGHT, "cub3d");
	mlx_hook(prog.win, 2, 1L << 0, ft_hooks_press, &prog);
	mlx_hook(prog.win, 3, 1L << 1, ft_hooks_release, &prog);
	prog.img.img = mlx_new_image(prog.mlx, WIDTH, HEIGHT);
	prog.img.addr = mlx_get_data_addr(prog.img.img, &(prog.img.bits_per_pixel),
			&(prog.img.line_length), &(prog.img.endian));
	init_textures(&prog);
	mlx_loop_hook(prog.mlx, ft_start, &prog);
	mlx_loop(prog.mlx);
	//ft_free_all(&prog);
	return (0);
}
int	main(int argc, char **argv)
{
	prog(argc, argv);
	return (0);
}


