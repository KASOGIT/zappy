/*
** action.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/include/server
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed Jun 15 18:22:54 2016 
** Last update Sun Jun 26 23:12:12 2016 
*/

#ifndef ACTION_H_
#define ACTION_H_

#include "zappy_error.h"
#include "handle_time.h"
#include "handle_client.h"
#include "server.h"

#define EXECUTED	1
#define WAITING		0

typedef struct s_handle_client	t_handle_client;
typedef struct s_server		t_server;

typedef struct	s_action
{
  /*
  ** attributs
  */
  double	_duration;
  t_handle_time	*_time;
  char		**_arg;
  void		(*func_cmd)(t_handle_client *client,
			    t_server *server,
			    char **arg);
  /*
  ** Methods
  */
  int	(*exec)(struct s_action *this,
		t_handle_client *client,
		int time_delay);
}		t_action;

/*
** Core methods
*/

void	action_set_methods(t_action *this);
void	action_init(t_action *this,
		    void (*func)(t_handle_client *, t_server *, char **),
		    char **arg,
		    int duration);
t_action	*action_create(void (*func)(t_handle_client *client,
					    t_server *,
					    char **),
			       char **arg,
			       int duration);

/*
** Methods
*/

int	action_exec(t_action *this,
		    t_handle_client *client,
		    int time_delay);

/*
** utils
*/

#endif /* !ACTION_H_ */
