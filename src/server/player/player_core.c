/*
** player_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/player
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue Jun 14 14:58:52 2016 
** Last update Sun Jun 26 22:37:31 2016 
*/

#include "player.h"

void	player_set_methods(t_player *this)
{
  this->add_action = &player_add_action;
  this->schedule_time = &player_schedule_time;
  this->schedule_actions = &player_schedule_actions;
  this->eat = &player_eat;
}

void	player_init(t_player *this, int pos_x, int pos_y, int time_delay)
{
  player_set_methods(this);
  this->_range = 1;
  this->_lvl = 1;
  this->_pos_x = pos_x;
  this->_pos_y = pos_y;
  this->_actions = list_create();
  this->_inventory = list_create();
  this->_time = handle_time_create();
  this->_unit_time = (1260.0f * (1.0f / (double)time_delay)) * 1000.0f;
  this->_way = NORTH;
  this->_time->start_chrono(this->_time);
}

t_player	*player_create(int pos_x, int pos_y, int time_delay)
{
  t_player	*p;

  p = malloc(sizeof(t_player));
  if (p == NULL)
    zappy_error("malloc player");
  player_init(p, pos_x, pos_y, time_delay);
  return (p);
}

void	player_destroy(t_player *this)
{
  list_destroy(this->_inventory);
  this->_inventory = NULL;
  handle_time_destroy(this->_time);
}
