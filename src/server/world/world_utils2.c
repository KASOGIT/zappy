/*
** world_utils2.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/world
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun 25 01:03:12 2016 
** Last update Sun Jun 26 04:14:22 2016 
*/

#include "world.h"

void	incr_view(t_world *this, t_way way, int *x, int *y)
{
  if (way == NORTH)
    {
      (*y)--;
      if (*y < 0)
	*y = this->_s_y - 1;
    }
  else if (way == SOUTH)
    {
      (*y)++;
      if (*y == this->_s_y)
	*y = 0;
    }
  else if (way == WEST)
    {
      (*x)--;
      if (*x < 0)
	*x = this->_s_x - 1;
    }
  else if (way == EAST)
    {
      (*x)++;
      if (*x == this->_s_x)
	*x = 0;
    }
}

int	fix_out_x(t_world *this, int x)
{
  int	offset;

  if (x >= this->_s_x)
    {
      offset = (x) - this->_s_x;
      return (offset);
    }
  else if (x < 0)
    {
      offset = this->_s_x + (x);
      return (offset);
    }
  return (x);
}

int	fix_out_y(t_world *this, int y)
{
  int	offset;

  if (y >= this->_s_y)
    {
      offset = (y) - this->_s_y;
      return (offset);
    }
  else if (y < 0)
    {
      offset = this->_s_y + (y);
      return (offset);
    }
  return (y);
}

char	*routine(t_server *server,
		 t_player *player,
		 int i,
		 char *str)
{
  int	j;

  j = 0;
  incr_view(server->_world, player->_way, &g_x, &g_y);
  while (j < i + 1)
    {
      if (player->_way == NORTH || player->_way == SOUTH)
	str = get_inter_case_x(server, g_x + j + 1, g_y, str);
      else if (player->_way == WEST || player->_way == EAST)
	str = get_inter_case_y(server, g_x, g_y + j + 1, str);
      j++;
    }
  str = get_next_case(server, g_x, g_y, str);
  j = 0;
  while (j < i + 1)
    {
      if (player->_way == NORTH || player->_way == SOUTH)
	str = get_inter_case_x2(server, g_x - j - 1, g_y, str);
      else if (player->_way == WEST || player->_way == EAST)
	str = get_inter_case_y2(server, g_x, g_y - j - 1, str);
      j++;
    }
  return (str);
}
