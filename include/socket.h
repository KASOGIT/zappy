/*
** socket.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Wed May  4 12:08:27 2016 
** Last update Sun May 29 11:45:13 2016 
*/

#ifndef SOCKET_H_
#define SOCKET_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "handle_client.h"

typedef struct s_handle_client t_handle_client;

typedef struct		s_socket
{
  int			_fd;
  int			_port;
  struct protoent	*_pe;
  struct sockaddr_in	s_in;
  int	(*socket_connect)(struct s_socket *this);
  int	(*socket_bind)(struct s_socket *this);
  int	(*socket_listen)(struct s_socket *this);
  int	(*socket_accept)(struct s_socket *this,
			 t_handle_client *client);
}			t_socket;

void	socket_set_methods(t_socket *this);
void	socket_error(t_socket *this, const char *err_msg);
void	socket_init(t_socket *this, int port, char *addr);
void	socket_destroy(t_socket *this);

#endif /* !SOCKET_H_ */
