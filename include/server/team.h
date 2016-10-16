/*
** team.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/include/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 15:46:29 2016 
** Last update Mon Jun 20 18:39:58 2016 
*/

#ifndef TEAM_H_
#define TEAM_H_

#include "list.h"
#include "handle_client.h"
#include "zappy_error.h"

typedef struct s_handle_client	t_handle_client;

typedef struct	s_team
{
  /*
  ** Attributes
  */
  t_list	*_client;
  char		*_name;
  int		_max_player;
  /*
  ** Methods
  */
  void	(*add_client)(struct s_team *this, t_handle_client *client);
}		t_team;

/*
** Core Methods
*/

void	team_set_methods(t_team *this);
t_team	*team_create(const char *name_team, int nplayers);
void	team_init(t_team *this, const char *name_team, int nplayers);
void	team_destroy(t_team *this);

/*
** Methods
*/

void	team_add_client(t_team *this, t_handle_client *client);

#endif /* !TEAM_H_ */
