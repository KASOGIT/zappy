/*
** droite_gauche.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/commands
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 20:27:57 2016 
** Last update Fri Jun 24 20:29:12 2016 
*/

#include "commands.h"

t_way_cmd	g_droite_cmd[4] =
  {
    {NORTH, EAST},
    {EAST,  SOUTH},
    {SOUTH, WEST},
    {WEST,  NORTH}
  };

t_way_cmd	g_gauche_cmd[4] =
  {
    {NORTH, WEST},
    {WEST,  SOUTH},
    {SOUTH, EAST},
    {EAST,  NORTH}
  };

void	PROTO_CMD(cmd_droite)
{
  int	i;

  (void)arg;
  (void)server;
  for (i = 0; i < 5; i++)
    {
      if (this->_player->_way == g_droite_cmd[i].WAY_ORIG)
        {
	  this->_player->_way = g_droite_cmd[i].NEW_WAY;
	  this->send_msg(this, "ok\n");
	  cmd_ppo(this, GRAPHICS);
	  return ;
        }
    }
}

void	PROTO_CMD(cmd_gauche)
{
  int	i;

  (void)arg;
  (void)server;
  for (i = 0; i < 5; i++)
    {
      if (this->_player->_way == g_gauche_cmd[i].WAY_ORIG)
        {
	  this->_player->_way = g_gauche_cmd[i].NEW_WAY;
	  this->send_msg(this, "ok\n");
	  cmd_ppo(this, GRAPHICS);
	  return ;
        }
    }
}
