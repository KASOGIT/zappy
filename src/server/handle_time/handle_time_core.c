/*
** handle_time_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/handle_time
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 18 20:08:45 2016 
** Last update Sat Jun 25 15:39:32 2016 
*/

#include "handle_time.h"

void        handle_time_set_methods(t_handle_time *this)
{
  this->start_chrono = &handle_time_start_chrono;
  this->get_mill_elapsed = &handle_time_get_mill_elapsed;
  this->get_micro_elapsed = &handle_time_get_micro_elapsed;
}

void        handle_time_init(t_handle_time *this)
{
  handle_time_set_methods(this);
}

t_handle_time   *handle_time_create()
{
  t_handle_time	*t;

  t = malloc(sizeof(t_handle_time));
  if (t == NULL)
    zappy_error("malloc handle_time");
  handle_time_init(t);
  return (t);
}

void	handle_time_destroy(__attribute__((unused))t_handle_time *this)
{
}
