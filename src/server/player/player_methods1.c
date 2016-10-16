/*
** player_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 17 18:00:08 2016 
** Last update Sun Jun 26 09:45:55 2016 
*/

#include "player.h"

void	player_add_action(t_player *this,
			  void (*ptr)(t_handle_client *, t_server *, char **),
			  char **arg,
			  int duration)
{
  this->_actions->push_back(this->_actions, action_create(ptr, arg, duration));
}

int		player_schedule_time(t_player *this,
				     __attribute__((unused))int time_delay)
{
  double	elapsed;

  elapsed = this->_time->get_mill_elapsed(this->_time);
  this->_unit_time = this->_unit_time - (elapsed - 0.01);
  this->_time->start_chrono(this->_time);
  if (this->_unit_time <= 0)
    return (PLAYER_DEAD);
  return (PLAYER_ALIVE);
}

void		player_schedule_actions(t_handle_client *this, int time_delay)
{
  t_elem	*it;
  t_elem	*end;
  t_action	*action;

  if (this->_player->_actions->size(this->_player->_actions) <= 0)
    return ;
  it = this->_player->_actions->begin(this->_player->_actions);
  end = this->_player->_actions->end(this->_player->_actions);
  while (it != end)
    {
      action = (t_action *)it->data(it);
      if (action->exec(action, this, time_delay) == EXECUTED)
	{
	  this->_player->_actions->erase_by_elem(this->_player->_actions,
						 action);
	  it = this->_player->_actions->begin(this->_player->_actions);
	}
      else
	it->next(it);
    }
  action = (t_action *)end->data(it);
  if (action->exec(action, this, time_delay) == EXECUTED)
    this->_player->_actions->erase_by_elem(this->_player->_actions, action);
}

void		player_eat(t_player *this)
{
  double	incr;

  incr = (double)((126.0f * (1.0f / (double)g_time_delay)) * 1000.0f);
  this->_unit_time += incr;
}
