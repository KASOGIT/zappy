/*
** server_methods3.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue Jun 14 17:38:31 2016 
** Last update Sat Jun 25 01:41:32 2016 
*/

#include "server.h"

void	server_create_actions(t_server *this)
{
  this->_users->for_each_arg(this->_users, &fill_actions_client, this);
  this->_client_graph->for_each_arg(this->_client_graph,
				    &exec_cmd_client_graph,
				    this);
}

void	server_send_msg_to_client_graph(t_server *this, char *msg)
{
  this->_client_graph->for_each_arg(this->_client_graph,
				    &send_msg_client_graph,
				    msg);
}

int	server_is_team_win(t_server *this)
{
  if (this->_world->_team->is_match_pred(this->_world->_team,
					 &check_team_win))
    {
      server_destroy(this);
      exit(EXIT_SUCCESS);
      return (1);
    }
  return (0);
}

int			server_get_lvl_users_by_id(t_server *this, int id)
{
  t_handle_client	*client;
  void			*elem;

  elem = this->_users->get_elem_by_pred_arg(this->_users,
					    &is_id_match,
					    &id);
  if (elem != NULL)
    {
      client = (t_handle_client *)elem;
      return (client->_id);
    }
  return (-1);
}

void	server_expulse_players(t_server *this, t_player *from)
{
  this->_users->for_each_arg(this->_users, &expulse_player, from);
}
