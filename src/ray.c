/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbrement <mbrement@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 03:33:27 by mbrement          #+#    #+#             */
/*   Updated: 2023/08/06 17:40:34 by mbrement         ###   ########lyon.fr   */
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
	int		mapx; // coordonée x du carré dans lequel est pos
	int		mapy; // coordonnée y du carré dans lequel est pos
	double		sidedistx; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
	double		sidedisty; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
	double		deltadistx; //distance que rayon parcours entre chaque point d'intersection vertical
	double		deltadisty; //distance que le rayon parcours entre chaque point d'intersection horizontal
	int		stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int		stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int		hit; // 1 si un mur a ete touche, 0 sinon
	int		side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	double		perpwalldist; // distance du joueur au mur
	int		lineheight; //hauteur de la ligne a dessiner
	int		drawstart; //position de debut ou il faut dessiner
	int		drawend; //position de fin ou il faut dessiner
	int		x; //permet de parcourir tous les rayons
}					t_ray;

void ft_verline(int x, int start, int end, int color, t_mlx *mlx)
{
	while (start < end)
	{
		my_mlx_pixel_put(mlx, x, start, color);
		start++;
	}
}

void ft_ray(t_mlx *mlx)
{
	t_ray	ray;
	int	color;

		ray.dirx = -0.66;
		ray.diry = 0;
		ray.planx = 0;
		ray.plany = 0.66;
	// while (1)
	// {
		ray.x = 0;
		while (ray.x < WIN_W)
		{
			ray.mapx = mlx->player->pos_x / 50;
			ray.mapy = mlx->player->pos_y / 50;
			ray.camerax = 2 * ray.x / (double)WIN_W - 1;
			ray.raydirx = ray.dirx + ray.planx * ray.camerax;
			ray.raydiry = ray.diry + ray.plany * ray.camerax;

			ray.deltadistx = fabs(1 / ray.raydirx);
			ray.deltadisty = fabs(1 / ray.raydiry);
			if (ray.raydirx == 0)
				ray.deltadistx = 1e30;
			if (ray.raydiry == 0)
				ray.deltadisty = 1e30;
			ray.hit = 0;
			if (ray.raydirx < 0)
			{
				ray.stepx = -1;
				ray.sidedistx = ((mlx->player->pos_x/50) - ray.mapx) * ray.deltadistx;
			}
			else
			{
				ray.stepx = 1;
				ray.sidedistx = (ray.mapx + 1.0 - (mlx->player->pos_x/50)) * ray.deltadistx;
			}
			if (ray.raydiry < 0)
			{
				ray.stepy = -1;
				ray.sidedisty = ((mlx->player->pos_y/50) - ray.mapy) * ray.deltadisty;
			}	
			else 
			{
				ray.stepy = 1;
				ray.sidedisty = (ray.mapy + 1.0 - (mlx->player->pos_y/50)) * ray.deltadisty;
			}
			while (ray.hit == 0)
			{
				if (ray.sidedistx < ray.sidedisty)
				{
					ray.sidedistx += ray.deltadistx;
					ray.mapx += ray.stepx;
					ray.side = 0;
				}
				else
				{
					ray.sidedisty += ray.deltadisty;
					ray.mapy += ray.stepy;
					ray.side = 1;
				}
				if (!is_valid_move(mlx, ray.mapy * 50, ray.mapx * 50))
				{
					// printf("mapy : %i mapx : %i\n", ray.mapy, ray.mapx);
					// printf("stepy : %i stepx : %i\n", ray.stepy, ray.stepx);
					ray.hit = 1;
				}
			}
			if (ray.side == 0)
				ray.perpwalldist = ray.sidedistx - ray.deltadistx;
			else
				ray.perpwalldist = ray.sidedisty - ray.deltadisty;
			ray.lineheight = (int)(WIN_H / ray.perpwalldist);
			
			// printf("lineheight : %i perpwalldist : %f\n", ray.lineheight, ray.perpwalldist);
			ray.drawstart = -ray.lineheight / 2 + WIN_H / 2;
			if (ray.drawstart < 0)
				ray.drawstart = 0;
			ray.drawend = ray.lineheight / 2 + WIN_H / 2;
			if (ray.drawend >= WIN_H)
				ray.drawend = WIN_H - 1;
			color = 0xFFFFA07A;
			if (ray.side == 1)
				color = color / 2;
			// printf("result : %i, %i\n", ray.drawstart, ray.drawend);
			ft_verline(ray.x, ray.drawstart, ray.drawend, color, mlx);
			ray.x+=1;
		}
	}
// }