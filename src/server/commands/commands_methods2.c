/*
** commands_methods2.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue Jun 21 00:51:41 2016 
** Last update Fri Jun 24 20:13:13 2016 
*/

#include "commands.h"

void		PROTO_CMD_GRAPH(cmd_msz)
{
  char		msg[256];

  sprintf(msg, "msz %d %d\n",
	  this->_parent->_world->_s_x,
	  this->_parent->_world->_s_y);
  if (whose == CLIENT)
    this->send_msg(this, msg);
  else
    this->_parent->send_msg_to_client_graph(this->_parent, msg);
}

void	    PROTO_CMD_GRAPH(cmd_bct)
{
  char      msg[1024];
  int       pos_x;
  int       pos_y;

  if (whose == CLIENT)
    {
      if (check_args_bct(this, &pos_x, &pos_y))
	{
	  this->send_msg(this, "sbp\n");
	  return;
	}
    }
  else
    {
      pos_x = this->_player->_pos_x;
      pos_y = this->_player->_pos_y;
    }
  prepare_bct_message(this, pos_x, pos_y, msg);
  if (whose == CLIENT)
    this->send_msg(this, msg);
  else
    this->_parent->send_msg_to_client_graph(this->_parent, msg);
}

void	    PROTO_CMD_GRAPH(cmd_mct)
{
  int       x;
  int       y;

  (void) whose;
  for (y = 0; y < this->_parent->_world->_s_y; y++)
    for (x = 0; x < this->_parent->_world->_s_x; x++)
      {
	cmd_bct_with_pos(this, x, y);
      }
}

void		PROTO_CMD_GRAPH(cmd_tna)
{
  char		*msg;
  t_elem	*it;
  t_elem	*end;

  if (this->_parent->_world->_team->size(this->_parent->_world->_team) == 0)
    return ;
  if ((msg = malloc(sizeof(char) * 256)) == NULL)
    zappy_error("malloc msg");
  it = this->_parent->_world->_team->begin(this->_parent->_world->_team);
  end = this->_parent->_world->_team->end(this->_parent->_world->_team);
  sprintf(msg, "tna");
  while (it != end)
    {
      msg = strcat(msg, " ");
      msg = strcat(msg, ((t_team *)it->data(it))->_name);
      it = it->next(it);
    }
  msg = strcat(msg, " ");
  msg = strcat(msg, ((t_team *)it->data(it))->_name);
  msg = strcat(msg, "\n");
  if (whose == CLIENT)
    this->send_msg(this, msg);
  else
    this->_parent->send_msg_to_client_graph(this->_parent, msg);
  free(msg);
}
