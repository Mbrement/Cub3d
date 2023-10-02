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
	double		pos_x;
	double		pos_y;
}					t_ray;

int	refresh_img(t_mlx *mlx)
{
	// Only one loop
	static int init = 0;

	if (init)
		return (0);
	//init = 1;

	mlx->data->img = mlx_new_image(mlx->mlx_init_ptr, WIN_W, WIN_H);
	mlx->data->addr = mlx_get_data_addr(mlx->data->img, &mlx->data->bits_per_pixel, &mlx->data->line_length, &mlx->data->endian);
	ft_ray (mlx);
	mlx_put_image_to_window(mlx->mlx_init_ptr, mlx->mlx_win_ptr, mlx->data->img, 0, 0);
	mlx_destroy_image(mlx->mlx_init_ptr, mlx->data->img);
	return(0);
}

int ft_tex_coo(t_ray ray, t_mlx mlx)
{
	double	wallx;
	double 	texx;

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

void ft_draw_vertical_north(t_mlx *mlx, int screen_x, int drawstart, int drawend, int x)
{
    int y;

    y = drawstart;
    while (y < drawend)
    {
        // Calculer l'indice du pixel dans la colonne x de la texture
        int tex_y = (int)((y - drawstart) * (mlx->wall->north_lenth / (double)(drawend - drawstart)));
        
        // Calculer l'adresse mémoire du pixel dans la texture
        char *tex_pixel_addr = mlx->wall->north_data.addr + (tex_y * *mlx->wall->north_data.size_line + x * (*mlx->wall->north_data.bits_py_px / 8));
        
        // Lire la couleur du pixel dans la texture
        unsigned int tex_color = *((unsigned int*)tex_pixel_addr);
        
        // Dessiner le pixel sur l'écran
        my_mlx_pixel_put(mlx, screen_x, y, tex_color);
        y++;
    }
}

void ft_draw_vertical_south(t_mlx *mlx, int screen_x, int drawstart, int drawend, int x)
{
    int y;

    y = drawstart;
    while (y < drawend)
    {
        // Calculer l'indice du pixel dans la colonne x de la texture
        int tex_y = (int)((y - drawstart) * (mlx->wall->south_lenth / (double)(drawend - drawstart)));
        
        // Calculer l'adresse mémoire du pixel dans la texture
        char *tex_pixel_addr = mlx->wall->south_data.addr + (tex_y * *mlx->wall->south_data.size_line + x * (*mlx->wall->south_data.bits_py_px / 8));
        
        // Lire la couleur du pixel dans la texture
        unsigned int tex_color = *((unsigned int*)tex_pixel_addr);
        
        // Dessiner le pixel sur l'écran
        my_mlx_pixel_put(mlx, screen_x, y, tex_color);
        y++;
    }
}

void ft_draw_vertical_east(t_mlx *mlx, int screen_x, int drawstart, int drawend, int x)
{
    int y;

    y = drawstart;
    while (y < drawend)
    {
        // Calculer l'indice du pixel dans la colonne x de la texture
        int tex_y = (int)((y - drawstart) * (mlx->wall->east_lenth / (double)(drawend - drawstart)));
        
        // Calculer l'adresse mémoire du pixel dans la texture
        char *tex_pixel_addr = mlx->wall->east_data.addr + (tex_y * *mlx->wall->east_data.size_line + x * (*mlx->wall->east_data.bits_py_px / 8));
        
        // Lire la couleur du pixel dans la texture
        unsigned int tex_color = *((unsigned int*)tex_pixel_addr);
        
        // Dessiner le pixel sur l'écran
        my_mlx_pixel_put(mlx, screen_x, y, tex_color);
        y++;
    }
}

void ft_draw_vertical_west(t_mlx *mlx, int screen_x, int drawstart, int drawend, int x)
{
    int y;

    y = drawstart;
    while (y < drawend)
    {
        // Calculer l'indice du pixel dans la colonne x de la texture
        int tex_y = (int)((y - drawstart) * (mlx->wall->west_lenth / (double)(drawend - drawstart)));
        
        // Calculer l'adresse mémoire du pixel dans la texture
        char *tex_pixel_addr = mlx->wall->west_data.addr + (tex_y * *mlx->wall->west_data.size_line + x * (*mlx->wall->west_data.bits_py_px / 8));
        
        // Lire la couleur du pixel dans la texture
        unsigned int tex_color = *((unsigned int*)tex_pixel_addr);
        
        // Dessiner le pixel sur l'écran
        my_mlx_pixel_put(mlx, screen_x, y, tex_color);
        y++;
    }
}

void	ft_get_color(t_mlx *mlx, t_ray ray, int screen_x, double x, double y)
{
	static double	half = (double)WIN_H / 2;

 
	double drawstart = (double)-ray.lineheight / 2 + half;
	double drawend = drawstart + ray.lineheight;

	if (ray.side == 1)
	{
		if (ray.raydiry < 0) // N
		{
			// printf("\033[31mN %f %f %f\033[0m\n", x, y, (x - floor(x)));
			ft_draw_vertical_north(mlx, screen_x, drawstart, drawend, (x - floor(x)) * mlx->wall->north_height);
		}
		else // S
		{
			// printf("\033[32mS %f %f %f\033[0m\n", x, y, 1. - x + floor(x));
			ft_draw_vertical_south(mlx, screen_x, drawstart, drawend, (1. - x + floor(x)) * mlx->wall->south_height);
		}
	}
	else
	{
		if (ray.raydirx < 0) // W
		{
			// printf("\033[33mW %f %f %f\033[0m\n", x, y, 1. - y + floor(y));
			ft_draw_vertical_east(mlx, screen_x, drawstart, drawend,  (1. - y + floor(y))* mlx->wall->west_height);
		}
		else // E
		{
			// printf("\033[34mE %f %f %f\033[0m\n", x, y, y - floor(y));
			ft_draw_vertical_west(mlx, screen_x, drawstart, drawend, (y - floor(y)) * mlx->wall->west_height);
		}
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

#include <math.h>

struct vector {
  double x;
  double y;
};

struct point {
  double x;
  double y;
};

struct vector get_u(double x, double y, double d) {
  double norm = sqrt(x * x + y * y);
  struct vector u = {
    .x = x * d / norm,
    .y = y * d / norm,
  };
  return u;
}

struct point get_collision_point(struct point P, struct vector v, double a) {
  double x = (a - P.y) / v.y * v.x;
  struct point collision_point = {
    .x = P.x + x,
    .y = a,
  };
  return collision_point;
}

struct point get_collision_point_x(struct point P, struct vector v, double a) {
  double y = (a - P.x) / v.x * v.y;
  struct point collision_point = {
    .x = a,
    .y = P.y + y,
  };
  return collision_point;
}

void ft_ray(t_mlx *mlx)
{
	t_ray	ray;
	double	angle_radiants;
	int		i;
	double	offset_x = mlx->player->pos_x - (int)mlx->player->pos_x;
	double	offset_y = mlx->player->pos_y - (int)mlx->player->pos_y;

	ft_prep_floor(mlx);
	angle_radiants = mlx->player->look * M_PI / 180.;
	ray.dirx = cos(angle_radiants);
    ray.diry = sin(angle_radiants);

	ray.planx = -ray.diry;
    ray.plany = ray.dirx;

	// i = 0;
	// while (i < WIN_W)7;
	int range = WIN_W;
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
			ray.sidedistx = (1. - offset_x) * ray.deltadistx;
			ray.stepx = 1;
		}
		if (ray.raydiry < 0)
		{
			ray.sidedisty = offset_y * ray.deltadisty;
			ray.stepy = -1;
		}
		else
		{
			ray.sidedisty = (1. - offset_y) * ray.deltadisty;
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
		struct vector p = get_u(ray.raydirx, ray.raydiry, ray.perpwalldist);
		struct point player = {
			.x = mlx->player->pos_x,
			.y = mlx->player->pos_y
		};
		struct vector v = {
			.x = ray.raydirx,
			.y = ray.raydiry
		};
		if (ray.side == 0)
		{
			double x_av = (double)round(mlx->player->pos_x + p.x);
			struct point wall_point = get_collision_point_x(player, v, x_av);
			// printf("%f, %f\n", mlx->player->pos_x + p.x, wall_point.x);
			ft_get_color(mlx, ray, i, x_av, wall_point.y);
		}
		else
		{
			double y_av = (double)round(mlx->player->pos_y + p.y);
			struct point wall_point = get_collision_point(player, v, y_av);
			// printf("%f, %f\n", mlx->player->pos_x + p.x, wall_point.x);
			ft_get_color(mlx, ray, i, wall_point.x, y_av);
		}
	}
}
