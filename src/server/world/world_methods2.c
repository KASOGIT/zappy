/*
** world_methods2.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun 23 14:41:48 2016 
** Last update Sat Jun 25 19:53:11 2016 
*/

#include "world.h"

int		g_x;
int		g_y;

char	*get_inter_case_x(t_server *server, int x, int y, char *str)
{
  int	p_x;

  p_x = fix_out_x(server->_world, x);
  str = strcat(str, server->is_player_at(server, p_x, y, 1));
  str = strcat(str, server->_world->_map[y][p_x]->see
	       (server->_world->_map[y][p_x]));
  str = strcat(str, ", ");
  return (str);
}

char	*get_inter_case_x2(t_server *server, int x, int y, char *str)
{
  int	n_x;

  n_x = fix_out_x(server->_world, x);
  str = strcat(str, server->is_player_at(server, n_x, y, 1));
  str = strcat(str, server->_world->_map[y][n_x]->see
	       (server->_world->_map[y][n_x]));
  return (str);
}

char	*get_inter_case_y(t_server *server, int x, int y, char *str)
{
  int	p_y;

  p_y = fix_out_y(server->_world, y);
  str = strcat(str, server->is_player_at(server, x, p_y, 1));
  str = strcat(str, server->_world->_map[p_y][x]->see
	       (server->_world->_map[p_y][x]));
  str = strcat(str, ", ");
  return (str);
}

char	*get_inter_case_y2(t_server *server, int x, int y, char *str)
{
  int	n_y;

  n_y = fix_out_y(server->_world, y);
  str = strcat(str, server->is_player_at(server, x, n_y, 1));
  str = strcat(str, server->_world->_map[n_y][x]->see
	       (server->_world->_map[n_y][x]));
  return (str);
}

char		*world_see(t_world *this, t_handle_client *client)
{
  int		i;
  t_player	*player;
  t_server	*server;
  char		*str;

  (void)this;
  i = 0;
  if ((str = malloc(sizeof(char) * 4096)) == NULL)
    zappy_error("malloc world see");
  server = client->_parent;
  player = client->_player;
  g_x = player->_pos_x;
  g_y = player->_pos_y;
  str = get_first_case(server, g_x, g_y, str);
  while (i != player->_range)
    {
      str = routine(server, player, i, str);
      i++;
    }
  str = strcat(str, "}\n");
  return (str);
}
