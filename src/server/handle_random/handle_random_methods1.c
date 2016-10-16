/*
** handle_random_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/handle_random
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Mon Jun 20 15:10:14 2016 
** Last update Fri Jun 24 20:38:03 2016 
*/

#include "handle_random.h"

int	handle_random_int_range(__attribute__((unused))
				t_handle_random *this,
				int min,
				int max)
{
  return (min + (int)rand() % (max - min));
}
