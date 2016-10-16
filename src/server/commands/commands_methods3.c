/*
** commands_methods3.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 20:07:07 2016 
** Last update Sun Jun 26 23:23:07 2016 
*/

#include "commands.h"

void		PROTO_CMD_GRAPH(cmd_ppo)
{
  char		msg[1024];

  memset(msg, '\0', 1024);
  sprintf(msg, "ppo #%d %d %d %d\n", this->_id,
	  this->_player->_pos_x, this->_player->_pos_y,
	  this->_player->_way + 1);
  if (whose == CLIENT)
    this->send_msg(this, msg);
  else
    this->_parent->send_msg_to_client_graph(this->_parent, msg);
}

void	PROTO_CMD_GRAPH(cmd_plv)
{
  int	id;
  int	lvl;
  char	msg[256];

  (void) whose;
  if (size_wordtab(this->_args) != 1
      || strlen(this->_args[0]) <= 1)
    {
      this->send_msg(this, "sbp\n");
      return ;
    }
  id = atoi(this->_args[0] + 1);
  lvl = this->_parent->get_lvl_users_by_id(this->_parent, id);
  if (lvl == -1)
    return ;
  sprintf(msg, "plv #%d %d\n", id, lvl);
  this->send_msg(this, msg);
}

void			PROTO_CMD_GRAPH(cmd_pin)
{
  char			msg[1024];
  t_handle_client	*player;

  memset(msg, '\0', 1024);
  reset_inventaire();
  if (whose == GRAPHICS)
    player = this;
  else
  {
    player = this->_parent->_users->
      get_elem_by_pred_arg(this->_parent->_users,
			   &get_user_by_id,
			   this->_args);
    if (!player)
    {
      this->send_msg(this, "sbp\n");
      return;
    }
  }
  pin_send_msg(player, whose, msg, this);
}

void	PROTO_CMD_GRAPH(cmd_sgt)
{
  char	msg[256];
  int	time;

  (void) whose;
  time = this->_parent->_world->_time_delay;
  sprintf(msg, "sgt %d\n", time);
  this->send_msg(this, msg);
}

void	PROTO_CMD_GRAPH(cmd_sst)
{
  int	new_time;

  if (size_wordtab(this->_args) == 0)
    {
      this->send_msg(this, "sbp\n");
      return ;
    }
  new_time = atoi(this->_args[0]);
  if (new_time <= 0)
    {
      this->send_msg(this, "sbp\n");
      return ;
    }
  this->_parent->_world->_time_delay = new_time;
  g_time_delay = new_time;
  cmd_sgt(this, whose);
}
