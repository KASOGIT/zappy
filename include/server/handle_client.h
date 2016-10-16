/*
** handle_client.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 14:43:11 2016 
** Last update Wed Jun 22 12:03:36 2016 
*/

#ifndef HANDLE_CLIENT_H_
#define HANDLE_CLIENT_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include "server.h"
#include "socket.h"
#include "commands.h"
#include "utils.h"
#include "circular_buffer.h"
#include "player.h"
#include "zappy_error.h"
#include "team.h"

typedef struct s_server	t_server;
typedef struct s_player	t_player;
typedef struct s_team	t_team;

#define GRAPH_ID	"GRAPHIC"

typedef enum		s_type_client
  {
    UNKNOWN,
    CLIENT_AI,
    EGG,
    CLIENT_GRAPH
  }			t_type_client;

typedef struct		s_handle_client
{
  /*
  ** Attributes
  */
  int			_id;
  int			_id_egg;
  t_team		*_team;
  t_type_client		_type;
  t_server		*_parent;
  t_player		*_player;
  int			_auth;
  struct sockaddr_in	_s_in;
  int			_fd;
  char			*_ip;
  t_circular_buffer	_buffer;
  char			*_cmd;
  char			**_args;
  /*
  ** Methods
  */
  void	(*read_cmd)(struct s_handle_client *this);
  void	(*send_msg)(struct s_handle_client *this,
				  const char *msg);
  void	(*fill_buff)(struct s_handle_client *this, t_server *server);
  int	(*get_cmd_id)(struct s_handle_client *this);
  int	(*get_cmd_graph_id)(struct s_handle_client *this);
  char	**(*cpy_arg)(struct s_handle_client *this);
  void	(*schedule_player)(struct s_handle_client *this, int time_delay);
}			t_handle_client;

/*
** Core methods
*/

void		handle_client_init(t_handle_client *this, t_server *parent);
t_handle_client	*handle_client_copy(t_handle_client *this);
void		handle_client_error(t_handle_client *this,
				    const char *err_msg);
void		handle_client_set_methods(t_handle_client *this);
void		handle_client_destroy(t_handle_client *this);

/*
** Methods
*/

void	handle_client_send_msg(t_handle_client *this,
			       const char *msg);
void	handle_client_send_err(t_handle_client *this, int c_err,
			       const char *msg, int end);
void	handle_client_send_rpl(t_handle_client *this, int c_rpl,
			       const char *msg, int end);
void	handle_client_read_cmd(t_handle_client *this);
void	handle_client_fill_buff(t_handle_client *this, t_server *server);
int	handle_client_get_cmd_id(t_handle_client *this);
int	handle_client_get_cmd_graph_id(t_handle_client *this);
char	**handle_client_cpy_arg(t_handle_client *this);
void	handle_client_schedule_player(t_handle_client *this, int time_delay);

/*
** Utils
*/

#endif /* !HANDLE_CLIENT_H_ */
