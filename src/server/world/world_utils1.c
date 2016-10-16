/*
** world_utils1.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Mon Jun 20 17:38:38 2016 
** Last update Sun Jun 26 16:32:46 2016 
*/

#include "world.h"

void	world_alloc_map(t_world *this)
{
  int	x;
  int	y;

  this->_map = malloc(sizeof(t_case **) * this->_s_y);
  if (this->_map == NULL)
    perror("malloc world alloc");
  y = 0;
  while (y != this->_s_y)
    {
      this->_map[y] = malloc(sizeof(t_case *) * this->_s_x);
      if (this->_map[y] == NULL)
	perror("malloc world alloc");
      x = 0;
      while (x != this->_s_x)
	{
	  this->_map[y][x] = case_create();
	  x++;
	}
      y++;
    }
}

void			schedule_client(void *arg1, void *arg2)
{
  t_handle_client	*client;
  int			time_delay;

  client = (t_handle_client *)arg1;
  time_delay = *((int *)arg2);
  if (client)
    client->schedule_player(client, time_delay);
}

void		schedule_team(void *arg1, void *arg2)
{
  t_team	*team;

  team = (t_team *)arg1;
  if (team)
    team->_client->for_each_arg(team->_client, &schedule_client, arg2);
}
