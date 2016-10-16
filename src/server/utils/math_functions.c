/*
** math_functions.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/utils
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 20:45:49 2016 
** Last update Fri Jun 24 20:46:03 2016 
*/

#include "commands.h"

double	calc_distance(const double x,
		      const double y,
		      const double x2,
		      const double y2)
{
  return (sqrt(pow(x2 - x, 2) + pow(y2 - y, 2)));
}
