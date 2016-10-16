/*
** world_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 17:17:08 2016 
** Last update Thu Jun 23 14:42:52 2016 
*/

#include "world.h"

void		world_add_team(t_world *this,
			       const char *name_team,
			       int size_team)
{
  t_team	*new;

  new = team_create(name_team, size_team);
  this->_team->push_back(this->_team, new);
}

void	world_schedule_world(t_world *this)
{
  if (this->_time->get_mill_elapsed(this->_time) >= 1000 / this->_time_delay)
    {
      this->fill_map(this);
      this->_time->start_chrono(this->_time);
    }
  this->_team->for_each_arg(this->_team, &schedule_team, &this->_time_delay);
}

void	world_fill_map(t_world *this)
{
  int	y;
  int	x;

  y = 0;
  while (y != this->_s_y)
    {
      x = 0;
      while (x != this->_s_x)
	{
	  this->_map[y][x]->fill(this->_map[y][x]);
	  x++;
	}
      y++;
    }
}
