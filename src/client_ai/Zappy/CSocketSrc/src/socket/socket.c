/*
** socket.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 12:34:53 2016 
** Last update Wed Jun 22 23:10:16 2016 Clement Oliva
*/

#include "socket.h"

static int	socket_connect(t_socket *this);
static int	socket_bind(t_socket *this);
static int	socket_listen(t_socket *this);

void	socket_set_methods(t_socket *this)
{
  this->connect = &socket_connect;
  this->bind = &socket_bind;
  this->listen = &socket_listen;
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
