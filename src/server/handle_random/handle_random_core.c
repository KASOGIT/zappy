/*
** handle_random_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/handle_random
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Mon Jun 20 15:06:46 2016 
** Last update Fri Jun 24 20:37:39 2016 
*/

#include "handle_random.h"

void            handle_random_set_methods(t_handle_random *this)
{
  this->int_range = &handle_random_int_range;
}

void            handle_random_init(t_handle_random *this)
{
  handle_random_set_methods(this);
  srand(time(NULL));
}

t_handle_random		*handle_random_create()
{
  t_handle_random	*r;

  r = malloc(sizeof(t_handle_random));
  if (r == NULL)
    zappy_error("malloc handle_random");
  handle_random_init(r);
  return (r);
}

void            handle_random_destroy(__attribute__((unused))
				      t_handle_random *this)
{
}
