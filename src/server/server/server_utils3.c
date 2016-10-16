/*
** server_utils3.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 15:25:03 2016 
** Last update Sun Jun 26 14:44:58 2016 Kévin Julien
*/

#include "server.h"

static void	north(t_handle_client *client, int *way)
{
  *way = 3;
  client->_player->_pos_y -= 1;
  if (client->_player->_pos_y < 0)
    client->_player->_pos_y = client->_parent->_world->_s_y - 1;
}

static void	east(t_handle_client *client, int *way)
{
  *way = 4;
  client->_player->_pos_x += 1;
  if (client->_player->_pos_x == client->_parent->_world->_s_x)
    client->_player->_pos_x = 0;
}

static void	south(t_handle_client *client, int *way)
{
  *way = 1;
  client->_player->_pos_y += 1;
  if (client->_player->_pos_y == client->_parent->_world->_s_y)
    client->_player->_pos_y = 0;
}

static void	west(t_handle_client *client, int *way)
{
  *way = 2;
  client->_player->_pos_x -= 1;
  if (client->_player->_pos_x == 0)
    client->_player->_pos_y = client->_parent->_world->_s_x - 1;
}

void                    expulse_player(void *arg1, void *arg2)
{
  t_handle_client       *client;
  t_player              *player;
  int                   way;
  char                  msg[256];

  client = (t_handle_client *)arg1;
  player = (t_player *)arg2;
  way = 0;
  if (client->_player != player
      && client->_player->_pos_x == player->_pos_x
      && client->_player->_pos_y == player->_pos_y)
    {
      if (player->_way == NORTH)
	north(client, &way);
      else if (player->_way == EAST)
	east(client, &way);
      else if (player->_way == SOUTH)
	south(client, &way);
      else if (player->_way == WEST)
	west(client, &way);
      sprintf(msg, "deplacement: %d\n", way);
    }
}
