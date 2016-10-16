/*
** server_utils1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun  3 00:56:12 2016 
** Last update Sun Jun 26 20:06:11 2016 
*/

#include "server.h"

int			is_same_fd(void *data, void *arg)
{
  int			fd;
  t_handle_client	*client;

  client = (t_handle_client *)data;
  fd = *((int *)arg);
  if (fd == client->_fd)
    return (1);
  return (0);
}

void	*comp_fd_client(void *c1, void *c2)
{
  return (((t_handle_client *)c1)->_fd > ((t_handle_client *)c2)->_fd ?
	  c1 : c2);
}

int		is_name_team_match(void *arg1, void *arg2)
{
  t_team	*t;
  char		*name;

  t = (t_team *)arg1;
  name = (char *)arg2;
  if (strcmp(t->_name, name) == 0)
    return (1);
  return (0);
}

void                    fill_actions_client(void *arg1, void *arg2)
{
  t_handle_client       *client;
  t_server              *server;
  int                   id;

  client = (t_handle_client *)arg1;
  (void)(server = (t_server *)arg2);
  if (client->_auth && client->_type == CLIENT_AI)
    {
      client->read_cmd(client);
      while (client->_cmd != NULL)
	{
	  id = client->get_cmd_id(client);
	  if (id != -1)
	    {
	      client->_player->add_action(client->_player,
					  g_cmd[id].func_cmd,
					  client->cpy_arg(client),
					  g_cmd[id].duration);
	    }
	  client->read_cmd(client);
	}
    }
}

void			exec_cmd_client_graph(void *arg1, void *arg2)
{
  t_handle_client	*client;
  t_server		*server;
  int			id;

  client = (t_handle_client *)arg1;
  (void)(server = (t_server *)arg2);
  if (client->_auth && client->_type == CLIENT_GRAPH)
    {
      client->read_cmd(client);
      while (client->_cmd != NULL)
	{
	  id = client->get_cmd_graph_id(client);
	  if (id != -1)
	    {
	      printf("cmd: [%s] graph executed\n", client->_cmd);
	      g_cmd_graph[id].func_cmd(client, CLIENT);
	    }
	  client->read_cmd(client);
	}
    }
}
