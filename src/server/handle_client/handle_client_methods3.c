/*
** handle_client_methods3.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 18 15:15:13 2016 
** Last update Sun Jun 26 22:37:23 2016 
*/

#include "handle_client.h"

void	handle_client_schedule_player(t_handle_client *this, int time_delay)
{
  char	msg[256];

  if (this->_player
      && this
      && this->_player->schedule_time(this->_player,
				      time_delay) == PLAYER_DEAD)
    {
      printf("player dead\n");
      sprintf(msg, "pdi #%d\n", this->_id);
      this->_parent->send_msg_to_client_graph(this->_parent, msg);
      if (this->_type == CLIENT_AI)
	this->_team->_client->erase_by_elem(this->_team->_client, this);
      this->_parent->_users->erase_by_elem(this->_parent->_users, this);
      if (this->_type == CLIENT_AI)
	this->send_msg(this, "mort\n");
      handle_client_destroy(this);
    }
  else
    this->_player->schedule_actions(this, time_delay);
}
