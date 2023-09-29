/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngennaro <ngennaro@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 03:33:27 by mbrement          #+#    #+#             */
/*   Updated: 2023/09/29 18:00:45 by ngennaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

typedef struct	s_ray
{
	double		dirx; //vecteur de direction (commence à -1 pour N, 1 pour S, 0 sinon)
	double		diry; //vecteur de direction (commence à -1 pour W, 1 pour E, 0 sinon)
	double		planx; //vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
	double		plany; //vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
	double		raydirx; //calcul de direction x du rayon
	double		raydiry; //calcul de direction y du rayon
	double		camerax; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
	double		sidedistx; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
	double		sidedisty; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
	double		deltadistx; //distance que rayon parcours entre chaque point d'intersection vertical
	double		deltadisty; //distance que le rayon parcours entre chaque point d'intersection horizontal
	int			stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int			stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int			hit; // 1 si un mur a ete touche, 0 sinon
	int			side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	double		perpwalldist; // distance du joueur au mur
	int			lineheight; //hauteur de la ligne a dessiner
	float		pos_x;
	float		pos_y;
}					t_ray;

int	refresh_img(t_mlx *mlx)
{
	// Only one loop
	static int init = 0;

	if (init)
		return (0);
	init = 1;

	mlx->data->img = mlx_new_image(mlx->mlx_init_ptr, WIN_W, WIN_H);
	mlx->data->addr = mlx_get_data_addr(mlx->data->img, &mlx->data->bits_per_pixel, &mlx->data->line_length, &mlx->data->endian);
	ft_ray (mlx);
	mlx_put_image_to_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr, mlx->data->img, 0, 0);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->data->img);
	return(0);
}

int ft_tex_coo(t_ray ray, t_mlx mlx)
{
	float	wallx;
	float 	texx;

	if (ray.side)
		wallx = mlx.player->pos_y + ray.perpwalldist * ray.raydiry;
	else
		wallx = mlx.player->pos_x + ray.perpwalldist * ray.raydirx;
	wallx = -floor(wallx);
	texx=(wallx * mlx.wall->east_height);
	if (ray.side && ray.raydirx > 0 )
		texx = mlx.wall->east_height - texx - 1;
	if (!ray.side && ray.diry < 0)
		texx = mlx.wall->east_height - texx - 1;
	return (texx);
}

void	ft_draw_vertical(t_mlx *mlx, int screen_x, int drawstart, int drawend, unsigned int color)
{
	for (int y = drawstart; y < drawend; y++)
	{
		my_mlx_pixel_put(mlx, screen_x, y, color);
	}
}

void	ft_get_color(t_mlx *mlx, t_ray ray, int screen_x)
{
	static double	half = (float)WIN_H / 2;

	double	step;
	double	tex_pos;
	double 	texy;
	char 	*get;
 
	float drawstart = (float)-ray.lineheight / 2 + half;
	float drawend = drawstart + ray.lineheight;


	if (ray.side == 1)
	{
		if (ray.raydiry < 0) // N
		{
			printf("%f %f\n", ray.pos_x, ray.pos_y);
			ft_draw_vertical(mlx, screen_x, drawstart, drawend, 0x00ffff);
		}
		else // S
			ft_draw_vertical(mlx, screen_x, drawstart, drawend, 0x0000ff);
	}
	else
	{
		if (ray.raydirx < 0) // W
			ft_draw_vertical(mlx, screen_x, drawstart, drawend, 0x00ff00);
		else // E
			ft_draw_vertical(mlx, screen_x, drawstart, drawend, 0xff00ff);
	}
		
	// 	texy = (int)floor(tex_pos) % (mlx.wall->east_height - 1);
	// 	// (void)texy;
	// 	tex_pos+=step;
	// 	get = (mlx.wall->east_data.addr + (int)(*(mlx.wall->east_data.size_line) * (int)(texy)  +  (ray.x * 4)));
	// 	// if (get < mlx.wall->east_data.addr + (char)(*mlx.wall->east_data.size_line * *mlx.wall->east_height + *mlx.wall->east_lenth))
	// 		// my_mlx_pixel_put(&mlx, ray.x, y, 0x0080ff);
	// 	// else
			// my_mlx_pixel_put(&mlx, ray.x, y, *(int *)get);
	// 		// write(1, "1",1);
	// 	y++;
}

void	ft_prep_floor(t_mlx *mlx)
{
	int	x;
	int	y;

	y = -1;
	while(++y<WIN_H / 2)
	{
		x = -1;
		while(++x < WIN_W)
		{
			my_mlx_pixel_put(mlx, x, y, mlx->map->celing_color);
		}
	}
	while(++y < WIN_H)
	{
		x = -1;
		while(++x < WIN_W)
		{
			my_mlx_pixel_put(mlx, x, y, mlx->map->floor_color);
		}
	}
}

void ft_ray(t_mlx *mlx)
{
	t_ray	ray;
	float	texx;
	double	angle_radiants;
	int		i;
	float	offset_x = mlx->player->pos_x - (int)mlx->player->pos_x;
	float	offset_y = mlx->player->pos_y - (int)mlx->player->pos_y;

	ft_prep_floor(mlx);
	angle_radiants = mlx->player->look * M_PI / 180.0;
	ray.dirx = cos(angle_radiants);
    ray.diry = sin(angle_radiants);

	ray.planx = -ray.diry;
    ray.plany = ray.dirx;

	// i = 0;
	// while (i < WIN_W)7;
	int range = 10;
	int offset = 0;
	i = WIN_W / 2 - range / 2 + offset;
	while (i < WIN_W / 2 + range / 2 + offset)
	{
		ray.pos_x = mlx->player->pos_x;
		ray.pos_y = mlx->player->pos_y;
		ray.camerax = 2 * i / (double)WIN_W - 1;
		ray.raydirx = ray.dirx + ray.planx * ray.camerax;
		ray.raydiry = ray.diry + ray.plany * ray.camerax;
		ray.deltadistx = fabs(1 / ray.raydirx);
		ray.deltadisty = fabs(1 / ray.raydiry);
		ray.hit = 0;
		if (ray.raydirx < 0)
		{
			ray.sidedistx = offset_x * ray.deltadistx;
			ray.stepx = -1;
		}
		else
		{
			ray.sidedistx = (1 - offset_x) * ray.deltadistx;
			ray.stepx = 1;
		}
		if (ray.raydiry < 0)
		{
			ray.sidedisty = offset_y * ray.deltadisty;
			ray.stepy = -1;
		}
		else
		{
			ray.sidedisty = (1 - offset_y) * ray.deltadisty;
			ray.stepy = 1;
		}
		int maxDist = 100;
		while (ray.hit == 0 && maxDist-- > 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.pos_x += ray.stepx;
				ray.side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.pos_y += ray.stepy;
				ray.side = 1;
			}
			if (!is_valid_move(mlx, ray.pos_x, ray.pos_y))
				ray.hit = 1;
		}
		i++;
		if (!ray.hit)
			continue;
		if (ray.side == 0)
			ray.perpwalldist = ray.sidedistx - ray.deltadistx;
		else
			ray.perpwalldist = ray.sidedisty - ray.deltadisty;
		ray.lineheight = (int)(WIN_H / ray.perpwalldist);
		ft_get_color(mlx, ray, i);
	}
}
