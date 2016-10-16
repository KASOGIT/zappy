/*
** world_utils3.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/world
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 25 01:06:39 2016 
** Last update Sat Jun 25 23:09:56 2016 
*/

#include "world.h"

char	*get_first_case(t_server *server, int x, int y, char *str)
{
  str[0] = '\0';
  str = strcat(str, "{");
  str = strcat(str, server->is_player_at(server, x, y, 0));
  str = strcat(str, server->_world->_map[y][x]->see
	       (server->_world->_map[y][x]));
  str = strcat(str, ", ");
  return (str);
}

char	*get_next_case(t_server *server, int x, int y, char *str)
{
  str = strcat(str, server->is_player_at(server, x, y, 1));
  str = strcat(str, server->_world->_map[y][x]->see
	       (server->_world->_map[y][x]));
  str = strcat(str, ", ");
  return (str);
}
