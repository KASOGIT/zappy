/*
** player.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu Jun  2 16:08:23 2016 
** Last update Sun Jun 26 23:13:53 2016 
*/

#ifndef PLAYER_H_
#define PLAYER_H_

#include "server.h"
#include "handle_client.h"
#include "handle_time.h"
#include "action.h"
#include "way.h"
#include "list.h"
#include "zappy_error.h"
#include "world.h"

#define PLAYER_ALIVE	1
#define PLAYER_DEAD		0
#define PLAYER_EAT		126
#define TO_MILL(x)		(x * 1000)
#define UNIT_LIFE_TO_TIME(x)	(x * PLAYER_EAT)
#define BASE_UNIT_LIFE	10
#define BASE_UNIT_TIME	TO_MILL(UNIT_LIFE_TO_TIME(BASE_UNIT_LIFE))

typedef struct s_handle_client	t_handle_client;
typedef struct s_server	t_server;

typedef struct	s_player
{
  /*
  ** attributes
  */
  int		_pos_x;
  int		_pos_y;
  t_list	*_actions;
  t_list	*_inventory;
  t_way		_way;
  int		_range;
  int		_lvl;
  double	_unit_time;
  t_handle_time	*_time;
  /*
  ** Methods
  */
  void	(*add_action)(struct s_player *this,
		      void (*ptr)(t_handle_client *, t_server *, char **),
		      char **arg,
		      int duration);
  int	(*schedule_time)(struct s_player *this, int time_delay);
  void	(*schedule_actions)(t_handle_client *this, int time_delay);
  void  (*eat)(struct s_player *this);
}		t_player;

/*
** Core methods
*/

void		player_set_methods(t_player *this);
t_player	*player_create(int pos_x, int pos_y, int time_delay);
void		player_init(t_player *this, int pos_x,
			    int pos_y, int time_delay);
void		player_destroy(t_player *this);
void		player_eat(t_player	*this);
/*
** Methods
*/

void	player_add_action(t_player *this,
			  void (*ptr)(t_handle_client *client,
				      t_server *server,
				      char **arg),
			  char **arg,
			  int duration);
int	player_schedule_time(t_player *this, int time_delay);
void	player_schedule_actions(t_handle_client *this, int time_delay);
/*
** Utils
*/

#endif /* !PLAYER_H_ */
