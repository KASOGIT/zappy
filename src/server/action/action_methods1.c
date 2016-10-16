/*
** action_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 18 19:04:17 2016 
** Last update Sun Jun 26 23:16:12 2016 
*/

#include "action.h"

int	action_exec(t_action *this,
		    t_handle_client *client,
		    int time_delay)
{
  int	mill_elapsed;

  (void)time_delay;
  mill_elapsed = this->_time->get_mill_elapsed(this->_time);
  if (mill_elapsed >= this->_duration / g_time_delay)
    {
      (*this->func_cmd)(client, client->_parent, this->_arg);
      return (EXECUTED);
    }
  return (WAITING);
}
