/*
** world.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/include/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed Jun  1 20:20:47 2016 
** Last update Sat Jun 25 17:25:08 2016 
*/

#ifndef WORLD_H_
#define WORLD_H_

#include "handle_time.h"
#include "player.h"
#include "handle_client.h"
#include "parse_arg.h"
#include "list.h"
#include "case.h"
#include "team.h"
#include "zappy_error.h"
#include "server.h"

typedef struct s_player	t_player;
typedef struct s_server	t_server;

typedef struct	s_world
{
  /*
  ** Attributes
  */
  t_list	*_team;
  int		_s_x;
  int		_s_y;
  int		_time_delay;
  t_handle_time	*_time;
  t_case	***_map;
  /*
  ** Methods
  */
  void	(*add_team)(struct s_world *this,
		    const char *name_team,
		    int size_team);
  void	(*schedule_world)(struct s_world *this);
  void	(*fill_map)(struct s_world *this);
  char	*(*see)(struct s_world *this, t_handle_client *client);
}		t_world;

extern int	g_time_delay;
extern int	g_x;
extern int	g_y;

/*
** Core methods
*/

void	world_set_methods(t_world *this);
t_world	*world_create(t_arg *arg);
void	world_init(t_world *this, t_arg *arg);
void	world_destroy(t_world *this);

/*
** Methods
*/

void	world_add_team(t_world *this,
		       const char *name_team,
		       int size_team);
void	world_schedule_world(t_world *this);
void	world_fill_map(t_world *this);
char	*world_see(t_world *this, t_handle_client *client);

/*
** Utils
*/

void	schedule_team(void *arg1, void *arg2);
void	schedule_client(void *arg1, void *arg2);
void	world_alloc_map(t_world *this);
void	incr_view(t_world *this, t_way way, int *x, int *y);
int     fix_out_x(t_world *this, int x);
int     fix_out_y(t_world *this, int y);
char	*routine(t_server *server,
		 t_player *player,
		 int i,
		 char *str);
char	*get_first_case(t_server *server, int x, int y, char *str);
char	*get_next_case(t_server *server, int x, int y, char *str);
char    *get_inter_case_x(t_server *server, int x, int y, char *str);
char    *get_inter_case_x2(t_server *server, int x, int y, char *str);
char    *get_inter_case_y(t_server *server, int x, int y, char *str);
char    *get_inter_case_y2(t_server *server, int x, int y, char *str);

#endif /* !WORLD_H_ */
