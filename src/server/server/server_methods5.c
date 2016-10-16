/*
** server_methods5.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 25 23:50:27 2016 
** Last update Sun Jun 26 00:26:27 2016 
*/

#include "server.h"

static void		change_time_player(void *arg1, void *arg2)
{
  t_handle_client	*client;
  int			time;

  client = (t_handle_client *)arg1;
  time = *((int *)arg2);
  client->_player->_unit_time /= 1000.0f;
  client->_player->_unit_time /= (1.0 / (double)g_time_delay);
  client->_player->_unit_time *= (1.0f / (double)time);
  client->_player->_unit_time *= 1000.0f;
}

void	server_reset_time_players(t_server *this, int new_time)
{
  this->_users->for_each_arg(this->_users,
			     &change_time_player,
			     &new_time);
}
