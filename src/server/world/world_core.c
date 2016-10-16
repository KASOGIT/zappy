/*
** world_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 15:33:41 2016 
** Last update Sat Jun 25 17:22:22 2016 
*/

#include "world.h"

int	g_time_delay;

void	world_set_methods(t_world *this)
{
  this->add_team = &world_add_team;
  this->schedule_world = &world_schedule_world;
  this->fill_map = &world_fill_map;
  this->see = &world_see;
}

t_world		*world_create(t_arg *arg)
{
  t_world	*new;

  new = malloc(sizeof(t_world));
  if (new == NULL)
    zappy_error("malloc");
  world_init(new, arg);
  return (new);
}

void	world_init(t_world *this, t_arg *arg)
{
  world_set_methods(this);
  this->_team = list_create();
  this->_s_x = arg->s_x;
  this->_s_y = arg->s_y;
  world_alloc_map(this);
  this->_time_delay = arg->speed;
  g_time_delay = this->_time_delay;
  this->_time = handle_time_create();
  this->_time->start_chrono(this->_time);
  this->fill_map(this);
}

void	world_destroy(t_world *this)
{
  list_destroy(this->_team);
}
