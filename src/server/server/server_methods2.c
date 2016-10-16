/*
** server_handle_client.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myirc
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Sun May 29 00:38:26 2016 
** Last update Sun Jun 26 21:33:31 2016 
*/

#include "server.h"

static void		fd_set_all(t_server *this)
{
  t_elem		*tmp;

  FD_ZERO(&this->_set);
  FD_SET(this->_sock->_fd, &this->_set);
  if (!this->_users->empty(this->_users))
    {
      tmp = this->_users->begin(this->_users);
      while (tmp != this->_users->end(this->_users))
	{
	  if (tmp->_data)
	    if (((t_handle_client *)tmp->_data)->_fd != -1)
	      FD_SET(((t_handle_client *)tmp->_data)->_fd, &this->_set);
	  tmp = tmp->_next;
	}
      if (tmp->_data)
	if (((t_handle_client *)tmp->_data)->_fd != -1)
	  FD_SET(((t_handle_client *)tmp->_data)->_fd, &this->_set);
    }
}

static void		server_routine(t_server *this, int i)
{
  void			*get_elem;
  t_handle_client	*client;

  if (FD_ISSET(i, &this->_set))
    {
      get_elem = this->_users->get_elem_by_pred_arg(this->_users,
						    &is_same_fd, &i);
      if (get_elem == NULL)
	{
	  if (this->connect_eggs(this) == 0)
	    {
	      client = malloc(sizeof(t_handle_client));
	      if (client == NULL)
		perror("malloc client error");
	      handle_client_init(client, this);
	      this->server_accept(this, client);
	      this->_users->push_back(this->_users, client);
	      client->send_msg(client, "BIENVENUE\n");
	    }
	}
      else
	((t_handle_client *)get_elem)->fill_buff((t_handle_client *)get_elem,
						 this);
    }
}

static void	routine_fd(t_server *this)
{
  int		i;

  i = this->_sock->_fd;
  while (i < FD_SETSIZE)
    server_routine(this, i++);
  this->auth_client(this);
  this->create_actions(this);
}

static void	routine_schedule(t_server *this)
{
  double	elapsed;

  elapsed = this->_time->get_mill_elapsed(this->_time);
  if (this->_world && elapsed >= 160)
    {
      this->_time->start_chrono(this->_time);
      this->_world->schedule_world(this->_world);
    }
}

void			server_handle_client(t_server *this)
{
  void			*max_elem;
  int			max_fd;
  struct timeval	tv;

  tv.tv_sec = 0;
  tv.tv_usec = 10;
  this->server_listen(this);
  signal(SIGPIPE, SIG_IGN);
  while (1)
    {
      fd_set_all(this);
      if ((max_elem = this->_users->max(this->_users,
					&comp_fd_client)) == NULL)
	max_fd = this->_sock->_fd;
      else
	max_fd = ((t_handle_client *)max_elem)->_fd;
      if (select(max_fd + 1, &this->_set, NULL, NULL, &tv) < 0)
	perror("select");
      else
	routine_fd(this);
      routine_schedule(this);
      usleep(10);
    }
}
