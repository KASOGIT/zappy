/*
** socket.h for Zappy in /home/oliva/_workspace_zappy/ai_client/Zappy/CSocketSrc/src/socket
** 
** Made by Clement Oliva
** Login   <oliva@epitech.net>
** 
** Started on  Sat Jun 18 18:59:39 2016 Clement Oliva
** Last update Wed Jun 22 23:10:49 2016 Clement Oliva
*/

#ifndef ZAPPY_SOCKET_H
#define ZAPPY_SOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

typedef struct		s_socket
{
  int			_fd;
  int			_port;
  struct protoent	*_pe;
  struct sockaddr_in	s_in;
  int	(*connect)(struct s_socket *this);
  int	(*bind)(struct s_socket *this);
  int	(*listen)(struct s_socket *this);
}			t_socket;

void	socket_set_methods(t_socket *this);
void	socket_error(t_socket *this, const char *err_msg);
void	socket_init(t_socket *this, int port, char *addr);
void	socket_destroy(t_socket *this);

#endif /* !ZAPPY_SOCKET_H */
