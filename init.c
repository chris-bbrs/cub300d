/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gjupy <gjupy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:48:41 by cboubour          #+#    #+#             */
/*   Updated: 2023/01/10 20:34:35 by gjupy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_structs(t_cub *cub)
{
	cub->player = malloc(sizeof(t_player));
	cub->ray = malloc(sizeof(t_ray));
	cub->draw_wall = malloc(sizeof(t_draw_wall));
	cub->tex = malloc(sizeof(t_tex));
	cub->img = ft_calloc(1, sizeof(t_img));
	if (cub->player == NULL || cub->ray == NULL || cub->draw_wall == NULL
		|| cub->tex == NULL || cub->img == NULL)
		exit(ENOMEM);
}

static void	create_floor_ceil(t_cub *cub)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	f_colour;
	uint32_t	c_colour;

	cub->img->b_img = mlx_new_image(cub->mlx, S_WIDTH, S_HEIGHT);
	f_colour = (cub->map->f[0] << 24) | (cub->map->f[1] << 16);
	f_colour = f_colour | (cub->map->f[2] << 8) | 255;
	c_colour = (cub->map->c[0] << 24) | (cub->map->c[1] << 16);
	c_colour = c_colour | (cub->map->c[2]  << 8) | 255;
	i = 0;
	while (i < S_HEIGHT)
	{
		j = 0;
		while (j < S_WIDTH)
		{
			if (i > S_HEIGHT / 2)
				mlx_put_pixel(cub->img->b_img, j, i, f_colour);
			else
				mlx_put_pixel(cub->img->b_img, j, i, c_colour);
			j++;
		}
		i++;
	}
}

static void	init_images(t_cub *cub)
{
	mlx_texture_t	*temp;

	cub->tex->tex = malloc(sizeof(mlx_texture_t *) * 4);
	cub->tex->tex[0] = mlx_load_png(cub->map->ea); // dino
	cub->tex->tex[1] = mlx_load_png(cub->map->we); // monkey
	cub->tex->tex[2] = mlx_load_png(cub->map->no); // aquatic
	cub->tex->tex[3] = mlx_load_png(cub->map->so); // lost
	temp = mlx_load_png("./textures/player.png");
	cub->img->player = mlx_texture_to_image(cub->mlx, temp);
	free(temp);
	create_floor_ceil(cub);
	if (mlx_image_to_window(cub->mlx, cub->img->b_img, 0, 0) == -1)
		rerror("put_background failed");
	if (mlx_image_to_window(cub->mlx, cub->img->player,
		(S_WIDTH - cub->img->player->width) / 2, S_HEIGHT- cub->img->player->height) == -1)
		rerror("put_horse failed");
	mlx_set_setting(MLX_STRETCH_IMAGE, 1);
}

void	initialize(t_cub *cub)
{
	init_structs(cub);
	set_player(cub);
	init_images(cub);
	cub->start_time = get_time();
	system("afplay -v 0.4 ./textures/ketamine_dreams.mp3 &");
	cub->pid[0] = get_pid("./textures/ketamine_dreams.mp3");
	cub->pid[1] = 0;
}
