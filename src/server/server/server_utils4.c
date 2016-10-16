/*
** server_utils4.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 15:30:32 2016 
** Last update Sun Jun 26 21:05:26 2016 
*/

#include "server.h"

void			send_msg_client_graph(void *arg1, void *arg2)
{
  t_handle_client	*client;
  char			*msg;

  client = (t_handle_client *)arg1;
  msg = (char *)arg2;
  if (msg != NULL)
    client->send_msg(client, msg);
}

int			check_player_max_lvl(void *arg)
{
  t_handle_client	*client;

  client = (t_handle_client *)arg;
  if (client->_player->_lvl == 6)
    return (1);
  return (0);
}

int		check_team_win(void *arg)
{
  char		msg[256];
  t_team	*team;
  t_server	*server;

  team = (t_team *)arg;
  if (team->_client->count_match_pred(team->_client,
				      &check_player_max_lvl) >= 6)
    {
      sprintf(msg, "seg %s\n", team->_name);
      server = ((t_handle_client *)
		team->_client->front(team->_client))->_parent;
      server->send_msg_to_client_graph(server, msg);
      return (1);
    }
  return (0);
}

int			is_id_match(void *arg1, void *arg2)
{
  t_handle_client	*client;
  int			id;

  client = (t_handle_client *)arg1;
  id = *((int *)arg2);
  if (client->_id == id)
    return (1);
  return (0);
}

void			connect_egg(void *arg1, void *arg2)
{
  int			*co;
  t_handle_client	*client;
  t_server		*server;
  char			msg[256];

  co = (int *)arg2;
  client = (t_handle_client *)arg1;
  server = client->_parent;
  if (client->_type == EGG)
    {
      client->_type = UNKNOWN;
      *co = 0;
      sprintf(msg, "ebo #%d\n", client->_id_egg);
      server->send_msg_to_client_graph(server, msg);
      server->_users->erase_by_elem(server->_users, client);
    }
}
