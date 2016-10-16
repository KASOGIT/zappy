/*
** server.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/include
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Tue May  3 13:32:11 2016 
** Last update Sun Jun 26 20:00:44 2016 
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "way.h"
#include "player.h"
#include "handle_client.h"
#include "list.h"
#include "socket.h"
#include "world.h"
#include "parse_arg.h"
#include "team.h"
#include "action.h"
#include "zappy_error.h"
#include "handle_random.h"
#include "handle_time.h"

typedef struct s_socket t_socket;
typedef struct s_handle_client t_handle_client;
typedef struct s_team	t_team;
typedef struct s_world	t_world;

typedef struct	s_server
{
  /*
  ** Attributes
  */
  t_handle_random	*_rand_gen;
  t_socket		*_sock;
  fd_set		_set;
  t_world		*_world;
  t_list		*_users;
  t_list		*_client_graph;
  int			_id_egg;
  t_handle_time		*_time;
  /*
  ** methods
  */
  void		(*server_listen)(struct s_server *this);
  void		(*server_handle_client)(struct s_server *this);
  void		(*server_accept)(struct s_server *this,
				 t_handle_client *client);
  void		(*auth_client)(struct s_server *this);
  t_team	*(*get_team_from_name)(struct s_server *this, char *name);
  void		(*create_actions)(struct s_server *this);
  void		(*send_msg_to_client_graph)(struct s_server *this, char *msg);
  int		(*is_team_win)(struct s_server *this);
  int		(*get_lvl_users_by_id)(struct s_server *this, int id);
  void		(*expulse_players)(struct s_server *this, t_player *from);
  int		(*connect_eggs)(struct s_server *this);
  char		*(*is_player_at)(struct s_server *this, int x, int y, int range);
  void		(*reset_time_players)(struct s_server *this, int new_time);
}		t_server;

/*
** Core methods
*/
void	server_error(t_server *this, const char *err_msg);
void	server_init(t_server *this, t_arg *arg);
void	server_set_methods(t_server *this);
void	server_destroy(t_server *this);
/*
** Methods
*/
void	server_handle_client(t_server *this);
void	server_auth_client(t_server *this);
t_team	*server_get_team_from_name(t_server *this, char *name);
void	server_listen(t_server *this);
void	server_accept(t_server *this, t_handle_client *client);
void	server_create_actions(t_server *this);
void	server_send_msg_to_client_graph(t_server *this, char *msg);
int	server_is_team_win(t_server *this);
int	server_get_lvl_users_by_id(t_server *this, int id);
void	server_expulse_players(t_server *this, t_player *from);
int	server_connect_eggs(t_server *this);
char	*server_is_player_at(t_server *this, int x, int y, int range);
void	server_reset_time_players(t_server *this, int new_time);
/*
** Utils
*/
int	is_same_fd(void *data, void *arg);
void	*comp_fd_client(void *c1, void *c2);
void	auth_client(void *arg1, void *arg2);
int	is_name_team_match(void *arg1, void *arg2);
void	fill_actions_client(void *arg1, void *arg2);
void	exec_cmd_client_graph(void *arg1, void *arg2);
void	send_msg_client_graph(void *arg1, void *arg2);
int	check_player_max_lvl(void *arg);
int	check_team_win(void *arg);
int	is_id_match(void *arg1, void *arg2);
void	expulse_player(void *arg1, void *arg2);
void	connect_egg(void *arg1, void *arg2);

#endif /* !SERVER_H_ */
