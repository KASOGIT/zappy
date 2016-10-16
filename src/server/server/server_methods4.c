/*
** server_methods4.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Fri Jun 24 14:37:35 2016 
** Last update Sat Jun 25 01:41:29 2016 
*/

#include "server.h"

static char		*routine_add(t_elem *it, int x, int y, int range)
{
  t_handle_client       *client;

  client = (t_handle_client *)it->data(it);
  if (client->_type == CLIENT_AI
      && client->_player->_pos_x == x
      && client->_player->_pos_y == y)
    if (range++ != 0)
      return (strdup("player "));
  return ("");
}

char                    *server_is_player_at(t_server *this,
					     int x, int y, int range)
{
  char                  *msg;
  t_elem                *it;
  t_elem                *end;

  if (this->_users->size(this->_users) == 0)
    return ("");
  msg = malloc(sizeof(char) * 4096);
  memset(msg, 0, 4096);
  if (msg == NULL)
    zappy_error("malloc is player at");
  it = this->_users->begin(this->_users);
  end = this->_users->end(this->_users);
  while (it != end)
    {
      msg = strcat(msg, routine_add(it, x, y, range));
      it = it->next(it);
    }
  msg = strcat(msg, routine_add(it, x, y, range));
  return (msg);
}

int	server_connect_eggs(t_server *this)
{
  int	co;

  co = 0;
  this->_users->for_each_arg(this->_users, &connect_egg, &co);
  return (co);
}

t_team	*server_get_team_from_name(t_server *this, char *name)
{
  return (this->_world->_team->get_elem_by_pred_arg(this->_world->_team,
						    &is_name_team_match,
						    name));
}
