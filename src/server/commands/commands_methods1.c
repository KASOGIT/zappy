/*
** commands_methods1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 17 15:34:25 2016 
** Last update Sun Jun 26 15:03:31 2016 Kévin Julien
*/

#include "commands.h"

void		PROTO_CMD(cmd_avance)
{
  int		i;

  (void) arg;
  if (!this->_player)
    return ;
  for (i = 0; i < 5; i++)
    {
      if (this->_player->_way == g_avance_cmd[i].WAY)
        {
	  g_avance_cmd[i].func_avance(this, server);
	  this->send_msg(this, "ok\n");
	  cmd_ppo(this, GRAPHICS);
	  return ;
        }
    }
}

void		cmd_voir(t_handle_client *this,
			 t_server *server,
			 UNUSED char **arg)
{
  char		*msg;

  if (!this->_player)
    return ;
  msg = server->_world->see(server->_world, this);
  this->send_msg(this, msg);
}

void        PROTO_CMD(cmd_expulse)
{
  (void)arg;
  if (!this->_player)
    return ;
  server->expulse_players(server, this->_player);
  this->send_msg(this, "ok\n");
}

void        PROTO_CMD(cmd_broadcast)
{
  if (size_wordtab(arg) == 0)
    {
      this->send_msg(this, "ko\n");
      return ;
    }
  this->_args = arg;
  server->_users->for_each_arg(server->_users, &broadcast, this);
}

void		cmd_connect_nbr(t_handle_client *this,
				t_server *server,
				UNUSED char **arg)
{
  t_team	*team;
  char		msg[256];

  if (size_wordtab(this->_args) == 0)
    {
      this->send_msg(this, "ko\n");
      return ;
    }
  team = server->get_team_from_name(server, this->_args[0]);
  if (team == NULL)
    this->send_msg(this, "ko\n");
  else
    {
      sprintf(msg, "%d\n",
	      team->_max_player - team->_client->size(team->_client));
      this->send_msg(this, msg);
    }
}
