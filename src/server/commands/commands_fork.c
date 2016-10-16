/*
** commands_fork.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 17:42:48 2016 
** Last update Sun Jun 26 21:22:32 2016 
*/

#include "commands.h"

void			egg_open(t_handle_client *this,
				 t_server *server,
				 UNUSED char **arg)
{
  char			msg[256];
  t_handle_client	*new;

  new = malloc(sizeof(t_handle_client));
  if (new == NULL)
    zappy_error("malloc egg open");
  handle_client_init(new, server);
  new->_player->_pos_x = this->_player->_pos_x;
  new->_player->_pos_y = this->_player->_pos_y;
  this->_team->_max_player++;
  new->_team = this->_team;
  new->_type = EGG;
  new->_id_egg = server->_id_egg++;
  server->_users->push_back(server->_users, new);
  sprintf(msg, "eht #%d\n", new->_id_egg);
  server->send_msg_to_client_graph(server, msg);
}

void	cmd_fork(t_handle_client *this, t_server *server, UNUSED char **arg)
{
  char	msg[256];

  this->_player->add_action(this->_player, &egg_open, NULL, TO_MILL(600));
  this->send_msg(this, "ok\n");
  sprintf(msg, "pfk #%d\n", this->_id);
  server->send_msg_to_client_graph(server, msg);
  sprintf(msg, "enw #%d #%d %d %d\n", server->_id_egg, this->_id,
	  this->_player->_pos_x,
	  this->_player->_pos_y);
  server->send_msg_to_client_graph(server, msg);
}
