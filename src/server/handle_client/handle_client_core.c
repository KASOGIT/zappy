/*
** handle_client_core.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_zappy/src/server/handle_client
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sat Jun  4 00:14:46 2016 
** Last update Sun Jun 26 22:15:51 2016 
*/

#include "handle_client.h"

void	handle_client_set_methods(t_handle_client *this)
{
  this->read_cmd = &handle_client_read_cmd;
  this->send_msg = &handle_client_send_msg;
  this->fill_buff = &handle_client_fill_buff;
  this->cpy_arg = &handle_client_cpy_arg;
  this->get_cmd_id = &handle_client_get_cmd_id;
  this->get_cmd_graph_id = &handle_client_get_cmd_graph_id;
  this->schedule_player = &handle_client_schedule_player;
}

void		handle_client_init(t_handle_client *this, t_server *parent)
{
  static int	id = 0;
  int		pos_x;
  int		pos_y;

  handle_client_set_methods(this);
  pos_x = parent->_rand_gen->int_range(parent->_rand_gen,
				       0,
				       parent->_world->_s_x);
  pos_y = parent->_rand_gen->int_range(parent->_rand_gen,
				       0,
				       parent->_world->_s_y);
  this->_player = player_create(pos_x, pos_y, parent->_world->_time_delay);
  this->_id = id++;
  this->_type = UNKNOWN;
  this->_parent = parent;
  this->_auth = 0;
  this->_fd = -1;
  this->_cmd = NULL;
  this->_args = NULL;
  this->_team = NULL;
  circular_buffer_init(&this->_buffer);
}

t_handle_client		*handle_client_copy(t_handle_client *this)
{
  t_handle_client	*cpy;

  handle_client_set_methods(this);
  cpy = malloc(sizeof(t_handle_client));
  if (cpy == NULL)
    zappy_error("handle client cpy");
  cpy->_fd = this->_fd;
  return (cpy);
}

void	handle_client_error(t_handle_client *this,
			    const char *err_msg)
{
  fprintf(stderr,
	  "[%d] Handle client error on func: %s\n",
	  (int)getpid(), err_msg);
  handle_client_destroy(this);
  exit(EXIT_FAILURE);
}

void	handle_client_destroy(t_handle_client *this)
{
  player_destroy(this->_player);
  if (close(this->_fd) == -1)
    {
      fprintf(stderr,
	      "[%d] Handle client error on func: close\n",
	      (int)getpid());
      exit(EXIT_FAILURE);
    }
  this->_team = NULL;
  if (this && this->_type == CLIENT_AI)
    free(this);
  this = NULL;
}
