/*
** team_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/team
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun  4 02:38:52 2016 
** Last update Sat Jul 30 16:06:21 2016 
*/

#include "team.h"

void	team_set_methods(t_team *this)
{
  this->add_client = &team_add_client;
}

void	team_init(t_team *this, const char *name_team, int max_player)
{
  team_set_methods(this);
  this->_client = list_create();
  this->_name = strdup(name_team);
  this->_max_player = max_player;
}

t_team		*team_create(const char *name_team, int max_player)
{
  t_team	*new;

  new = malloc(sizeof(t_team));
  if (new == NULL)
    zappy_error("malloc team create");
  team_init(new, name_team, max_player);
  return (new);
}

void	team_destroy(t_team *this)
{
  list_destroy(this->_client);
  free(this->_name);
}
