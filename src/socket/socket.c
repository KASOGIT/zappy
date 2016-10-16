/*
** socket.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 12:34:53 2016 
** Last update Sun May 29 12:26:26 2016 
*/

#include "socket.h"

static int	socket_connect(t_socket *this);
static int	socket_bind(t_socket *this);
static int	socket_listen(t_socket *this);
static int	socket_accept(t_socket *this,
			      t_handle_client *client);

void	socket_set_methods(t_socket *this)
{
  this->socket_connect = &socket_connect;
  this->socket_bind = &socket_bind;
  this->socket_listen = &socket_listen;
  this->socket_accept = &socket_accept;
}

static int	socket_connect(t_socket *this)
{
  if (connect(this->_fd,
	      (const struct sockaddr *)&this->s_in,
	      sizeof(this->s_in)) == -1)
    {
      socket_error(this, "connect");
      return (-1);
    }
  return (0);
}

static int	socket_bind(t_socket *this)
{
  if (bind(this->_fd,
	   (const struct sockaddr *)&this->s_in,
	   sizeof(this->s_in)) == -1)
    {
      socket_error(this, "bind");
      return (-1);
    }
  return (0);
}

static int	socket_listen(t_socket *this)
{
  if (listen(this->_fd, SOMAXCONN) == -1)
    socket_error(this, "listen");
  return (0);
}

static int	socket_accept(t_socket *this,
			      t_handle_client *client)
{
  socklen_t	len;

  len = sizeof(client->_s_in);
  client->_fd = accept(this->_fd,
		       (struct sockaddr *)&client->_s_in,
		       &len);
  if (client->_fd == -1)
    socket_error(this, "accept");
  return (0);
}
