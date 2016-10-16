/*
** action_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/action
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 17 18:24:20 2016 
** Last update Fri Jun 24 15:39:55 2016 
*/

#include "action.h"

void	action_set_methods(t_action *this)
{
  this->exec = &action_exec;
}

void	action_init(t_action *this,
		    void (*func)(t_handle_client *, t_server *, char **),
		    char **arg,
		    int duration)
{
  action_set_methods(this);
  this->func_cmd = func;
  this->_arg = arg;
  this->_duration = duration;
  this->_time = handle_time_create();
  this->_time->start_chrono(this->_time);
}

t_action	*action_create(void (*func)(t_handle_client *,
					    t_server *, char **),
			       char **arg,
			       int duration)
{
  t_action	*a;

  a = malloc(sizeof(t_action));
  if (a == NULL)
    zappy_error("malloc action create");
  action_init(a, func, arg, duration);
  return (a);
}
