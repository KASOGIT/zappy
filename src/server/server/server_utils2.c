/*
** server_utils2.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 15:05:13 2016 
** Last update Sun Jun 26 12:56:37 2016 
*/

#include "server.h"

static void	add_player(t_handle_client *client,
			   t_server *server,
			   t_team *team)
{
  char		buff[256];

  client->_type = CLIENT_AI;
  client->_team = team;
  team->add_client(team, client);
  sprintf(buff, "%d\n",
	  team->_max_player - team->_client->size(team->_client));
  client->send_msg(client, buff);
  sprintf(buff, "%d %d\n", server->_world->_s_x, server->_world->_s_y);
  client->send_msg(client, buff);
  sprintf(buff, "pnw #%d %d %d 1 1 %s\n",
	  client->_id,
	  client->_player->_pos_x,
	  client->_player->_pos_y,
	  team->_name);
  server->send_msg_to_client_graph(server, buff);
}

void                    auth_client(void *arg1, void *arg2)
{
  t_handle_client       *client;
  t_server              *server;
  t_team                *team;

  client = (t_handle_client *)arg1;
  server = (t_server *)arg2;
  if (!client->_auth)
    {
      client->read_cmd(client);
      if (!client->_cmd)
	return ;
      client->_auth = 1;
      team = server->get_team_from_name(server, client->_cmd);
      if (team
	  && team->_client->size(team->_client) != team->_max_player)
	add_player(client, server, team);
      else if (strcmp(GRAPH_ID, client->_cmd) == 0)
	{
	  client->_type = CLIENT_GRAPH;
	  client->_team = NULL;
	  server->_client_graph->push_back(server->_client_graph, client);
	}
      else
	printf("team not found or full\n");
    }
}
