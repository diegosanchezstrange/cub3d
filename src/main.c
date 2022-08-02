/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsanchez <dsanchez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */ 
/*   Created: 2022/07/23 18:31:29 by dsanchez          #+#    #+#             */ 
/*   Updated: 2022/07/25 20:18:44 by mclerico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	ft_hooks(int keycode, t_cub *vars)
{
	if (keycode == KEY_ESC)
	{
		ft_free_all(vars);
		exit(0);
		return (1);
	}
	return (0);
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
	return (1);
}

int	main(int argc, char **argv)
{
	t_cub	prog;

	if (argc != 2)
		return (1);
	if (!ft_init_prog(&prog))
		return (1);
	if (!ft_parse_file(argv[1], &prog))
	{
		ft_free_cub(&prog);
		return (2);
	}
	prog.mlx = mlx_init();
	prog.win = mlx_new_window(prog.mlx, W, H, "cub3d");
	mlx_hook(prog.win, 2, 1L << 0, ft_hooks, &prog);
	prog.img.img = mlx_new_image(prog.mlx, W, H);
	prog.img.addr = mlx_get_data_addr(prog.img.img, &(prog.img.bits_per_pixel),
			&(prog.img.line_length), &(prog.img.endian));
	ft_start(prog);
	mlx_loop(prog.mlx);
	return (0);
}
